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

public class ColorMessage
{
    public static void load()
    {
        String os = System.getProperty("os.name");

        if(os.equals("Linux"))
        {
            ANSI_RESET = "\033[0m";
            ANSI_BOLD = "\033[1m";
            ANSI_BOLD_RED = "\033[1;31m";
            ANSI_BOLD_YELLOW = "\033[1;33m";
            ANSI_BOLD_BLUE = "\033[1;34m";
        }
    }

    public static String bold(String text)
    {
        return ANSI_BOLD + text + ANSI_RESET;
    }

    public static String red(String text)
    {
        return ANSI_BOLD_RED + text + ANSI_RESET;
    }

    public static String yellow(String text)
    {
        return ANSI_BOLD_YELLOW + text + ANSI_RESET;
    }

    public static String debug()
    {
        return ANSI_BOLD_BLUE + "DEBUG: " + ANSI_RESET;
    }

    public static String debug(String function)
    {
        return ANSI_BOLD_BLUE + "DEBUG<" + function + ">: " + ANSI_RESET;
    }

    public static String warning()
    {
        return ANSI_BOLD_YELLOW + "WARNING: " + ANSI_RESET;
    }

    public static String error()
    {
        return ANSI_BOLD_RED + "ERROR: " + ANSI_RESET;
    }

    public static String error(String function)
    {
        return ANSI_BOLD_RED + "ERROR<" + function + ">: " + ANSI_RESET;
    }

    private static String ANSI_RESET = "";
    private static String ANSI_BOLD = "";
    private static String ANSI_BOLD_RED = "";
    private static String ANSI_BOLD_YELLOW = "";
    private static String ANSI_BOLD_BLUE = "";
}
