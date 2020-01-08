// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package com.eprosima.log;

import com.eprosima.log.ColorMessage;

public class Log
{
    public static final int DEBUG = 0;
    public static final int INFO = 1;
    public static final int WARNING = 2;
    public static final int ERROR = 3;

    public static void printDebug(String message)
    {
        if(m_level <= DEBUG)
            System.out.println(ColorMessage.debug() + message);
    }

    public static void printDebug(String function, String message)
    {
        if(m_level < DEBUG)
            System.out.println(ColorMessage.debug(function) + message);
    }

    public static int m_level = ERROR;
}
