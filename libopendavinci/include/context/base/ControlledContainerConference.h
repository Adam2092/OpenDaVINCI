/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef CONTEXT_BASE_CONTROLLEDCONTAINERCONFERENCE_H_
#define CONTEXT_BASE_CONTROLLEDCONTAINERCONFERENCE_H_

// platform.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/opendavinci.h"
#include "context/base/SendContainerToSystemsUnderTest.h"

namespace core { namespace io { namespace conference { class ContainerListener; } } }

namespace context {
    namespace base {

        /**
         * This interface provides methods to get data sent to
         * ControlledContainerConference and to send data to a
         * ControlledContainerConference.
         */
        class OPENDAVINCI_API ControlledContainerConference : public SendContainerToSystemsUnderTest {
            public:
                virtual ~ControlledContainerConference();

                /**
                 * This method adds a ContainerListener to receive data from
                 * a system under test.
                 *
                 * @param cl ContainerListener to add.
                 */
                virtual void add(core::io::conference::ContainerListener *cl) = 0;
        };

    }
} // context::base

#endif /*CONTEXT_BASE_CONTROLLEDCONTAINERCONFERENCE_H_*/
