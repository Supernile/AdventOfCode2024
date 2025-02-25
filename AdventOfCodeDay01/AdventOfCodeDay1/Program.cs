/*
To do:
Subroutine to open datafile and compile the two lists
Subroutine to sort the two lists by value
Subroutine to compare each item in the list to the other list and calculate the differece (sum together to get total distance)
*/
using System;
using System.Collections.Generic;

class Program
{
    static int GetNumberOfItems(string FILEPATH)
    {
        //Checks how many lines are in the file so the arrays can be initialised with the correct length
        int numberOfItems = 0;
        using (StreamReader sr = new StreamReader(FILEPATH))
        {
            string line = string.Empty;
            while ((line = sr.ReadLine()) != null)
            {
                numberOfItems++;
            }
        }
        return numberOfItems;
    }

    static (int[], int[]) CreateListsFromFile(int numberOfItems, string FILEPATH)
    {
        //Opens the file and reads the two lists into memory
        int[] list1 = new int[numberOfItems];
        int[] list2 = new int[numberOfItems];
        string[] rowItems = new string[2];

        using (StreamReader sr = new StreamReader(FILEPATH))
        {
            string line = string.Empty;
            int i = 0;
            while((line = sr.ReadLine()) != null)
            {
                //From the file, reads the two numbers and splits them into two items in the array rowItems. From here they are assigned to their respective arrays (i used as indexer)
                rowItems = line.Split("   ");
                list1[i] = Convert.ToInt32(rowItems[0]);
                list2[i] = Convert.ToInt32(rowItems[1]);
                i++;
            }
        }
        return (list1, list2);
    }

    static int CompareLists(int[] list1, int[] list2)
    {
        int totalDifference = 0;
        int indexDifference = 0;

        for (int i = 0; i < list1.Length; i++)
        {
            if (list1[i] > list2[i])
            {
                indexDifference = list1[i] - list2[i];
            }
            else if (list1[i] < list2[i])
            {
                indexDifference = list2[i] - list1[i];
            }
            else
            {
                indexDifference = 0;
            }

            totalDifference += indexDifference;
        }

        return totalDifference;
    }

    static int CalculateSimilarityScore(int[] list1, int[] list2)
    {
        //Calculates how similar the two arrays are by multiplying the number in the first list by how often it appears in the second list and summing the value for each line
        //If I wanted to optimise this, I could try saving each number's comparisons so they could be reused again (eg. first 3 generates score of 9 so all 3's will generate score of 9)
        int totalSimilarityScore = 0;
        int indexSimilarityScore = 0;
        int numberOfOccurencesInList2 = 0;
        for (int i = 0; i < list1.Length; i++)
        {
            numberOfOccurencesInList2 = 0;
            for (int j = 0; j < list2.Length; j++)
            {
                if ((list1[i] == list2[j]))
                {
                    numberOfOccurencesInList2++;
                }
            }
            indexSimilarityScore = numberOfOccurencesInList2 * list1[i];
            totalSimilarityScore += indexSimilarityScore;
        }
        return totalSimilarityScore;
    }

    static void Main()
    {
        //Takes two lists from the file in memory and compares the difference between the two lists (each element's difference totalled)
        const string FILEPATH = "test.txt";
        int[] list1;
        int[] list2;
        int numberOfItems = GetNumberOfItems(FILEPATH);
        (list1, list2) = CreateListsFromFile(numberOfItems, FILEPATH);
        //Sort the lists into ascending order
        Array.Sort(list1);
        Array.Sort(list2);
        int totalDistance = CompareLists(list1, list2);
        int similarityScore = CalculateSimilarityScore(list1, list2);
        Console.WriteLine($"The total distance between the two lists is {totalDistance}");
        Console.WriteLine($"The similarity score of the two lists is {similarityScore}");
    }
}