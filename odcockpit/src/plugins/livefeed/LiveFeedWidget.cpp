/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2016 Christian Berger
 * Copyright (C) 2008 - 2011 (as monitor component) Christian Berger, Bernhard Rumpe
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <QtCore>
#include <QtGui>

#include <cstring>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/Visitable.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "plugins/livefeed/LiveFeedWidget.h"
#include "plugins/livefeed/MessageToTupleVisitor.h"

#include "automotivedata/GeneratedHeaders_AutomotiveData_Helper.h"

namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {

    namespace plugins {

        namespace livefeed {

            using namespace std;
            using namespace odcore::base;
            using namespace odcore::data;

            LiveFeedWidget::LiveFeedWidget(const PlugIn &/*plugIn*/, QWidget *prnt) :
                QWidget(prnt),
                m_dataViewMutex(),
                m_dataView(),
                m_dataToType() {
                // Set size.
                setMinimumSize(640, 480);

                // Layout manager.
                QGridLayout* mainBox = new QGridLayout(this);

                //ListView and header construction
                m_dataView = unique_ptr<QTreeWidget>(new QTreeWidget(this));
                m_dataView->setColumnCount(2);
                QStringList headerLabel;
                headerLabel << tr("Message") << tr("Value");
                m_dataView->setColumnWidth(0, 200);
                m_dataView->setColumnWidth(1, 200);
                m_dataView->setHeaderLabels(headerLabel);

                //add to Layout
                mainBox->addWidget(m_dataView.get(), 0, 0);

                // Set layout manager.
                setLayout(mainBox);
            }

            LiveFeedWidget::~LiveFeedWidget() {}

            void LiveFeedWidget::nextContainer(Container &container) {
                Lock l(m_dataViewMutex);
                transformContainerToTree(container);
            }

            void LiveFeedWidget::transformContainerToTree(Container &container) {
                vector<pair<string, string> > entries;
                entries.push_back(make_pair("Sent", container.getSentTimeStamp().getYYYYMMDD_HHMMSSms()));
                entries.push_back(make_pair("Received", container.getReceivedTimeStamp().getYYYYMMDD_HHMMSSms()));

                // Map attributes from message to the entries.
                MessageToTupleVisitor mttv(entries);
                bool successfullyDelegated = false;
                GeneratedHeaders_AutomotiveData_Helper::delegateVistor(container, mttv, successfullyDelegated);

                if (successfullyDelegated) {
                    Message msg = mttv.getMessage();
                    //create new Header if needed
                    if (m_dataToType.find(msg.getShortName()) == m_dataToType.end()) {
                        QTreeWidgetItem *newHeader = new QTreeWidgetItem(m_dataView.get());
                        newHeader->setText(0, msg.getShortName().c_str());
                        m_dataToType[msg.getShortName()] = newHeader;
                    }

                    QTreeWidgetItem *entry = m_dataToType[msg.getShortName()];
                    if (static_cast<uint32_t>(entry->childCount()) != entries.size()) {
                        entry->takeChildren();

                        for (uint32_t i = 0; i < entries.size(); i++) {
                            QTreeWidgetItem *sent = new QTreeWidgetItem();
                            entry->insertChild(i, sent);
                        }
                    }

                    // Map tuples of <string, string> to the tree.
                    for (uint32_t i = 0; i < entries.size(); i++) {
                        QTreeWidgetItem *child = entry->child(i);
                        child->setText(0, entries.at(i).first.c_str());
                        child->setText(1, entries.at(i).second.c_str());
                    }
                }
            }
        }
    }
}
