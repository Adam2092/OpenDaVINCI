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

#ifndef OPENDAVINCI_CORE_BASE_BUFFEREDFIFOQUEUE_H_
#define OPENDAVINCI_CORE_BASE_BUFFEREDFIFOQUEUE_H_

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/FIFOQueue.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/exceptions/Exceptions.h"

namespace odcore {
    namespace base {

        using namespace std;

        /**
         * This interface encapsulates all methods necessary for a buffered FIFO.
         * A buffered FIFO allows indexed access to the elements without removing
         * them.
         */
        class OPENDAVINCI_API BufferedFIFOQueue : public FIFOQueue {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                BufferedFIFOQueue(const BufferedFIFOQueue &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                BufferedFIFOQueue& operator=(const BufferedFIFOQueue &);

            public:
                /**
                 * Constructor.
                 *
                 * @param bufferSize Maximum size for this buffer fifo.
                 */
                BufferedFIFOQueue(const uint32_t &bufferSize);

                virtual ~BufferedFIFOQueue();

                virtual void enter(const data::Container &container);

                /**
                 * This method returns the index of the last element.
                 *
                 * @return Index of the last element or -1 if the FIFO is empty.
                 */
                int32_t getIndexOfLastElement() const;

                /**
                 * This method returns the elements at the current index.
                 *
                 * @param index Index of the element to be retrieved.
                 * @return Element at the given index.
                 * @throws ArrayIndexOutOfBoundsException if the index is invalid.
                 */
                const data::Container getElementAt(const uint32_t &index) const throw (exceptions::ArrayIndexOutOfBoundsException);

                /**
                 * This method returns whether the queue is full or not.
                 *
                 * @return true if the queue-size reached it's maximum.
                 */
                virtual bool isFull() const;

            private:
                uint32_t m_bufferSize;
        };

    }
} // odcore::base

#endif /*OPENDAVINCI_CORE_BASE_BUFFEREDFIFOQUEUE_H_*/
