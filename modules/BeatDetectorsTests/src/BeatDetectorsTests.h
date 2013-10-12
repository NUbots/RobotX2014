/*
 * This file is part of BeatDetectorsTests.
 *
 * AudioInput is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * BeatDetectorsTests is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with BeatDetectorsTests.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 Joshua Kearns <joshau-k@hotmail.com>
 */

#ifndef MODULES_BEATDETECTORSTESTS_H
#define	MODULES_BEATDETECTORSTESTS_H

#include <NUClear.h>


namespace modules {

    class BeatDetectorsTests : public NUClear::Reactor {
    private:
        
    public:
        explicit BeatDetectorsTests(NUClear::PowerPlant* plant);
        ~BeatDetectorsTests();
    };
}

#endif	/* BEATDETECTORSTESTS_H */
