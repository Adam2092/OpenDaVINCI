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

#include "opendavinci/odcontext/base/Runner.h"
#include "opendavinci/odcontext/base/TimeConstants.h"
#include "opendavinci/odcore/wrapper/Time.h"

namespace odcontext {
    namespace base {

        Runner::Runner() {}

        Runner::~Runner() {}

        bool Runner::hasFinished() const {
            return false;
        }

        bool Runner::needsExecution(const odcore::wrapper::Time &t) const {
            bool retVal = false;
            if (getFrequency() > 0) {
                const uint32_t THIS_RUN_AT_TIME = static_cast<uint32_t>(TimeConstants::ONE_SECOND_IN_MILLISECONDS / getFrequency());

                // Consider the current seconds only if the module is running with a frequency slower than 1 Hz.
                const uint32_t CURRENT_MILLISECONDS = ( (THIS_RUN_AT_TIME > TimeConstants::ONE_SECOND_IN_MILLISECONDS) ? t.getSeconds() * TimeConstants::ONE_SECOND_IN_MILLISECONDS : 0 )
                                                      + t.getPartialMicroseconds() / TimeConstants::ONE_MILLISECOND_IN_MICROSECONDS;

                retVal = ( (CURRENT_MILLISECONDS % THIS_RUN_AT_TIME) == 0 );
            }

            return (retVal && !hasFinished());
        }

    }
} // odcontext::base
