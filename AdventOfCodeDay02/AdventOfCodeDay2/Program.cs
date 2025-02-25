class Program()
{
    static bool IsSafe(int[] report, bool firstCall)
    {
        bool ascending = false;
        bool reportSafe = true;
        bool problemDampenerUsed = true;
        if (firstCall)
        {
            problemDampenerUsed = false;
        }
        int removedIndex = -1;
        // Check to see if the sequence is ascending or descending
        if (report[1] > report[0])
        {
            ascending = true;
        }
        else if (report[1] < report[0])
        {
            ascending = false;
        }
        else
        {
            reportSafe = false;
        }

        //A report is safe if each number in the list is either descending or ascending (by less than 3 at a time)
        for (int i = 1; i < report.Length; i++)
        {
            if (ascending)
            {
                //Checks first whether the index is less than the last (if it is then the report is not safe) then if the index is three or more apart (if it is then report not safe)
                if (report[i] <= report[i - 1])
                {
                    reportSafe = false;
                    if (problemDampenerUsed == false)
                    {
                        removedIndex = i;
                        problemDampenerUsed = true;
                    }
                }
                //Checks first whether the index is greater than the last (if it is then the report is not safe) then if the index is three or more apart (if it is then report not safe)
                else if (((report[i] - report[i - 1]) > 3) || ((report[i] - report[i - 1]) < 1))
                {
                    reportSafe = false;
                    if (problemDampenerUsed == false)
                    {
                        removedIndex = i;
                        problemDampenerUsed = true;
                    }
                }
            }
            else
            {
                //Checks first whether the index is greater than the last (if it is then the report is not safe) then if the index is three or more apart (if it is then report not safe)
                if (report[i] >= report[i - 1])
                {
                    reportSafe = false;
                    if (problemDampenerUsed == false)
                    {
                        removedIndex = i;
                        problemDampenerUsed = true;
                    }
                }
                else if (((report[i - 1] - report[i]) > 3) || ((report[i - 1] - report[i]) < 1))
                {
                    reportSafe = false;
                    if (problemDampenerUsed == false)
                    {
                        removedIndex = i;
                        problemDampenerUsed = true;
                    }
                }

                if (i <= report.Length - 1)
                {
                    if (report[i] == report[i - 1])
                    {
                        reportSafe = false;
                    }
                }

            }
        }
        
        if (!reportSafe && firstCall == true)
        {
            int i = 0;
            while (reportSafe == false && i < report.Length)
            {
                int[] newReport = CreateNewReport(report, i);
                reportSafe = IsSafe(newReport, false);
                i++;
            }
        }
        
        return reportSafe;
    }

    static int[] CreateNewReport(int[] report, int removedIndex)
    {
        int[] newReport = new int[(report.Length - 1)];
        int j = 0;
        for (int i = 0; i < report.Length; i++)
        {
            if (i != removedIndex)
            {
                newReport[j] = report[i];
                j++;
            }
        }
        return newReport;

    }
    static int CheckSafeReports()
    {
        const string FILEPATH = "test.txt";
        int numberOfSafeReports = 0;
        List<string> stringReport = new List<string>();
        bool reportSafe = false;

        using (StreamReader sr = new StreamReader(FILEPATH))
        {
            string line;
            while ((line = sr.ReadLine()) != null)
            {
                stringReport.AddRange(line.Split(" "));
                int[] report = new int[stringReport.Count];
                for (int i = 0; i < stringReport.Count; i++)
                {
                    report[i] = Convert.ToInt32(stringReport[i]);
                }
                reportSafe = IsSafe(report, true);
                if (reportSafe)
                {
                    numberOfSafeReports++;
                }
                stringReport = new List<string>();
            }
        }

        return numberOfSafeReports;
    }

    static void Main()
    {
        int numberOfSafeReports = CheckSafeReports();
        Console.WriteLine($"There are {numberOfSafeReports} safe reports");
    }
}