class Program
{
    static string ExtractCommand(string inputString, int startingIndex)
    {
        //extracts the command from the string
        int num = 0;
        bool commaReached = false;
        string command = string.Empty;
        int numberLength = 0;

        if (inputString.Substring(startingIndex , 4) == "mul(")
        {
            //command += "mul(";
            for (int i = startingIndex + 4; i < startingIndex + 12; i++)
            {
                if (int.TryParse("" + inputString[i], out num) && numberLength < 3)
                {
                    command += inputString[i];
                    numberLength += 1;
                }
                else if (inputString[i] == ',' && numberLength >= 1 && commaReached != true)
                {
                    command += inputString[i];
                    numberLength = 0;
                    commaReached = true;
                }
                else if (inputString[i] == ')' && numberLength >= 1 && commaReached == true)
                {
                    //command += inputString[i];
                    //Makes i out of range to end the for loop
                    i += 8;
                }
                else
                {
                    command = string.Empty;
                    //Makes i out of range to end the for loop
                    i += 8;
                }
            }
        }

        return command;
    }


    static List<string> RemoveInvalidCommands(string inputString)
    {
        //A valid command must be in the format mul(x,y) where x and y are numbers with up to three digits
        int startingIndex = 0;
        int endIndex = 0;
        bool doCommands = true;
        string command = string.Empty;
        List<string> commands = new List<string>();

        for (int i = 0; i < inputString.Length; i++)
        {
            if (inputString[i] == 'm')
            {
                startingIndex = i;
                if (doCommands == true)
                {
                    command = ExtractCommand(inputString, startingIndex);
                    if (command != "")
                    {
                        commands.Add(command);
                    }
                }
            }
            else if (inputString[i] == 'd')
            {
                startingIndex = i;
                if (inputString.Substring(startingIndex, 7) == "don't()")
                {
                    doCommands = false;
                }
                else if (inputString.Substring(startingIndex, 4) == "do()")
                {
                    doCommands = true;
                }
            }
        }

        return commands;
    }

    static int PerformCommands(List<string> commands)
    {
        string command = string.Empty;
        string[] nums = new string[2];
        int num1 = 0;
        int num2 = 0;
        int result = 0;
        int totalResult = 0;

        for (int i = 0; i <= commands.Count - 1; i++)
        {
            command = commands[i];
            nums = command.Split(',');
            num1 = Convert.ToInt32(nums[0]);
            num2 = Convert.ToInt32(nums[1]);
            result = num1 * num2;
            totalResult += result;
        }

        return totalResult;
    }


    static void Main()
    {
        const string FILEPATH = "test.txt";

        string inputString = File.ReadAllText(FILEPATH);
        List<string> commands = RemoveInvalidCommands(inputString);
        int result = PerformCommands(commands);
        
        Console.WriteLine(result);
    }
}