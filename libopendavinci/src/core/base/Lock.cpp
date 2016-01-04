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

#include "core/base/Lock.h"
#include "core/base/Mutex.h"

namespace core {
    namespace base {

        Lock::Lock(Mutex &mutex) :
                m_mutex(&mutex),
                m_sharedPointerToSharedMemory() {
            m_mutex->lock();
        }

        Lock::Lock(core::SharedPointer<core::wrapper::SharedMemory> sp) :
                m_mutex(NULL),
                m_sharedPointerToSharedMemory(sp) {
            m_sharedPointerToSharedMemory->lock();
        }

        Lock::~Lock() {
            if (m_mutex != NULL) {
                m_mutex->unlock();
            }
            else {
                m_sharedPointerToSharedMemory->unlock();
            }
        }

    }
} // core::base
