using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using static System.Math;
using System.Threading.Tasks;
using System.Collections;

namespace TicTacToeGUI
{
   
    public static class GlobalClass{
        private static List<double> scores_list = new List<double>();
        private static List<string> initials_list = new List<string>();
        private static BitArray playerGameState = new BitArray(64);
        private static BitArray compGameState = new BitArray(64);
        public static BitArray board = new BitArray(64);
        public static List<int> dataX = new List<int>(4);
        public static List<int> dataO = new List<int>(4);
        public static int MIN = int.MinValue;
        public static int MAX = int.MaxValue;
        public static int DEPTH_MAX = 2;
        private static ulong playerUint = 0;
        private static ulong compUint = 0;
        public static bool playerTurn = true;
        private static string initials = ""; 

        private static string t = "test" ;
        private static Boolean userWon = false; 
    

        public static List<double> DV{
            get { return scores_list; }
            set { scores_list = value; }
        }
        public static string pl_in
        {
            get { return initials; }
            set { initials = value; }
        }
        public static Boolean whoWON
        {
            get { return userWon; }
            set { userWon= value; }

        }
        public static string changeText {
            get { return t; }
            set { t = value;  }

        }

        public static List<string> IN
        {
            get { return initials_list; }
            set { initials_list = value; }
        }

        public static bool pTurn
        {
            get { return playerTurn; }
            set { playerTurn = value; }
        }

        public static ulong pUint
        {
            get { return playerUint; }
            set { playerUint = value; }
        }

        public static ulong cUint
        {
            get { return compUint; }
            set { compUint = value; }
        }

        //handles player's board
        public static BitArray pGame
        {
            get { return playerGameState; }
            set { playerGameState = value; }
        }

        //handles comp's board
        public static BitArray cGame
        {
            get { return compGameState; }
            set { compGameState = value; }
        }

        //converts bit array to 64 bit number
        public static ulong GetIntFromBitArray(BitArray bitArray)
        {
            var array = new byte[8];
            bitArray.CopyTo(array, 0);
            return BitConverter.ToUInt64(array, 0);
        }

        public static List<int> indexToPoint(int index)
        {
            //assumes index starts at zero and goes to 63
            //x,y,z range from 0-3
            List<int> L = new List<int>();
            int z = index / 16;
            index = index % 16;
            int y = index / 4;
            index = index % 4;
            int x = index;
            L.Add(x);
            L.Add(y);
            L.Add(z);

            return L;
        }

        public static int pointToIndex(List<int> point)
        {
            return point[0] + point[1] * 4 + point[2] * 16;
        }

        public static int checkWin()
        {
            //winner = 0 -> no winner yet
            //winner = 1 -> player won
            //winner = 2 -> comp won
            //winner = 3 -> draw (no more moves left)
            int winner = 0;

            //check for player/comp win
            BitArray currentCheck = new BitArray(64);

            //if player just went, check if the player won
            if (GlobalClass.playerTurn)
            {
                currentCheck = GlobalClass.pGame;
            }
            //otherwise the computer just went
            else
            {
                currentCheck = GlobalClass.cGame;
            }
            //check for win on most recent play
            //winVal must be 4 for winner to be declared
            int winVal = 0;
            bool check = true;
            while (check)                                     //FIXME: Might not need this while
            {
                //check columns on each sub-board
                for (int z = 0; z < 4; ++z)
                {
                    for (int x = 0; x < 4; ++x)
                    {
                        for (int y = 0; y < 4; ++y)
                        {
                            List<int> tempPoint = new List<int> { x, y, z };
                            int tempIndex = pointToIndex(tempPoint);
                            if (currentCheck.Get(tempIndex) == true)
                            {
                                winVal += 1;
                            }
                        }
                        if (winVal == 4)
                        {
                            //someone has won
                            break;
                        }
                        else
                        {
                            //reset winVal for next check
                            winVal = 0;
                        }
                    }
                }

                if(winVal == 4)
                {
                    //someone has won
                    break;
                }
                else
                {
                    //reset winVal for next check
                    winVal = 0;
                }

                //check vertical columns
                for (int x = 0; x < 4; ++x)
                {
                    for (int y = 0; y < 4; ++y)
                    {
                        for (int z = 0; z < 4; ++z)
                        {
                            List<int> tempPoint = new List<int> { x, y, z };
                            int tempIndex = pointToIndex(tempPoint);
                            if (currentCheck.Get(tempIndex) == true)
                            {
                                winVal += 1;
                            }
                        }
                        if (winVal == 4)
                        {
                            //someone has won
                            break;
                        }
                        else
                        {
                            //reset winVal for next check
                            winVal = 0;
                        }
                    }
                }

                if (winVal == 4)
                {
                    //someone has won
                    break;
                }
                else
                {
                    //reset winVal for next check
                    winVal = 0;
                }


                //check rows on each sub-board
                for (int z = 0; z < 4; ++z)
                {
                    for (int y = 0; y < 4; ++y)
                    {
                        for (int x = 0; x < 4; ++x)
                        {
                            List<int> tempPoint = new List<int> { x, y, z };
                            int tempIndex = pointToIndex(tempPoint);
                            if (currentCheck.Get(tempIndex) == true)
                            {
                                winVal += 1;
                            }
                        }
                        if (winVal == 4)
                        {
                            //someone has won
                            break;
                        }
                        else
                        {
                            //reset winVal for next check
                            winVal = 0;
                        }
                    }
                }

                if (winVal == 4)
                {
                    //someone has won
                    break;
                }
                else
                {
                    //reset winVal for next check
                    winVal = 0;
                }


                //check vertical rows
                for (int y = 0; y < 4; ++y)
                {
                    for (int x = 0; x < 4; ++x)
                    {
                        for (int z = 0; z < 4; ++z)
                        {
                            List<int> tempPoint = new List<int> { x, y, z };
                            int tempIndex = pointToIndex(tempPoint);
                            if (currentCheck.Get(tempIndex) == true)
                            {
                                winVal += 1;
                            }
                        }
                        if (winVal == 4)
                        {
                            //someone has won
                            break;
                        }
                        else
                        {
                            //reset winVal for next check
                            winVal = 0;
                        }
                    }
                }

                if (winVal == 4)
                {
                    //someone has won
                    break;
                }
                else
                {
                    //reset winVal for next check
                    winVal = 0;
                }

                //check sub-board left-right diagonals
                for (int z = 0; z < 4; ++z)
                {
                    for (int x = 0; x < 4; ++x)
                    {
                        int y = x;
                        List<int> tempPoint = new List<int> { x, y, z };
                        int tempIndex = pointToIndex(tempPoint);
                        if (currentCheck.Get(tempIndex) == true)
                        {
                            winVal += 1;
                        }
                    }
                    if (winVal == 4)
                    {
                        //someone has won
                        break;
                    }
                    else
                    {
                        //reset winVal for next check
                        winVal = 0;
                    }
                }

                if (winVal == 4)
                {
                    //someone has won
                    break;
                }
                else
                {
                    //reset winVal for next check
                    winVal = 0;
                }

                //check sub-board right-left diagonals
                for (int z = 0; z < 4; ++z)
                {
                    for (int x = 0; x < 4; ++x)
                    {
                        int y = 3 - x;
                        List<int> tempPoint = new List<int> { x, y, z };
                        int tempIndex = pointToIndex(tempPoint);
                        if (currentCheck.Get(tempIndex) == true)
                        {
                            winVal += 1;
                        }
                    }
                    if (winVal == 4)
                    {
                        //someone has won
                        break;
                    }
                    else
                    {
                        //reset winVal for next check
                        winVal = 0;
                    }
                }

                if (winVal == 4)
                {
                    //someone has won
                    break;
                }
                else
                {
                    //reset winVal for next check
                    winVal = 0;
                }


                //check vertical left-right diagonals
                for (int z = 0; z < 4; ++z)
                {
                    int x = z;
                    int y = z;
                    List<int> tempPoint = new List<int> { x, y, z };
                    int tempIndex = pointToIndex(tempPoint);
                    if (currentCheck.Get(tempIndex) == true)
                    {
                        winVal += 1;
                    }
                }

                if (winVal == 4)
                {
                    //someone has won
                    break;
                }
                else
                {
                    //reset winVal for next check
                    winVal = 0;
                }

                //check vertical right-left diagonals
                for (int z = 3; z >= 0; --z)
                {
                    int y = z;
                    int x = 3 - z;
                    List<int> tempPoint = new List<int> { x, y, z };
                    int tempIndex = pointToIndex(tempPoint);
                    if (currentCheck.Get(tempIndex) == true)
                    {
                        winVal += 1;
                    }
                }

                if (winVal == 4)
                {
                    //someone has won
                    break;
                }
                else
                {
                    //reset winVal for next check
                    winVal = 0;
                }



                check = false;
            }//end of checks


            BitArray checker = new BitArray(64);
            checker.SetAll(true);

            BitArray tempGame = new BitArray(GlobalClass.pGame);

            if (winVal == 4)
            {
                if (GlobalClass.playerTurn)
                {
                    //player won
                    winner = 1;
                }
                else
                {
                    //comp won
                    winner = 2;
                }
            }
            else if(tempGame.Or(GlobalClass.cGame) == checker)
            {
                //draw
                winner = 3;
            }
            //else no winner
            
            

            return winner;
        }

        public static int Winner(bool player, BitArray Game)
        {
            //winner = 0 -> no winner yet
            //winner = 1 -> player won
            //winner = 2 -> comp won
            //winner = 3 -> draw (no more moves left)
            int winner = 0;

            //check for player/comp win
            BitArray currentCheck = new BitArray(64);

            currentCheck = Game;

            //check for win on most recent play
            //winVal must be 4 for winner to be declared
            int winVal = 0;
            bool check = true;
            while (check)                                     //FIXME: Might not need this while
            {
                //check columns on each sub-board
                for (int z = 0; z < 4; ++z)
                {
                    for (int x = 0; x < 4; ++x)
                    {
                        for (int y = 0; y < 4; ++y)
                        {
                            List<int> tempPoint = new List<int> { x, y, z };
                            int tempIndex = pointToIndex(tempPoint);
                            if (currentCheck.Get(tempIndex) == true)
                            {
                                winVal += 1;
                            }
                        }
                        if (winVal == 4)
                        {
                            //someone has won
                            break;
                        }
                        else
                        {
                            //reset winVal for next check
                            winVal = 0;
                        }
                    }
                }

                if (winVal == 4)
                {
                    //someone has won
                    break;
                }
                else
                {
                    //reset winVal for next check
                    winVal = 0;
                }

                //check vertical columns
                for (int x = 0; x < 4; ++x)
                {
                    for (int y = 0; y < 4; ++y)
                    {
                        for (int z = 0; z < 4; ++z)
                        {
                            List<int> tempPoint = new List<int> { x, y, z };
                            int tempIndex = pointToIndex(tempPoint);
                            if (currentCheck.Get(tempIndex) == true)
                            {
                                winVal += 1;
                            }
                        }
                        if (winVal == 4)
                        {
                            //someone has won
                            break;
                        }
                        else
                        {
                            //reset winVal for next check
                            winVal = 0;
                        }
                    }
                }

                if (winVal == 4)
                {
                    //someone has won
                    break;
                }
                else
                {
                    //reset winVal for next check
                    winVal = 0;
                }


                //check rows on each sub-board
                for (int z = 0; z < 4; ++z)
                {
                    for (int y = 0; y < 4; ++y)
                    {
                        for (int x = 0; x < 4; ++x)
                        {
                            List<int> tempPoint = new List<int> { x, y, z };
                            int tempIndex = pointToIndex(tempPoint);
                            if (currentCheck.Get(tempIndex) == true)
                            {
                                winVal += 1;
                            }
                        }
                        if (winVal == 4)
                        {
                            //someone has won
                            break;
                        }
                        else
                        {
                            //reset winVal for next check
                            winVal = 0;
                        }
                    }
                }

                if (winVal == 4)
                {
                    //someone has won
                    break;
                }
                else
                {
                    //reset winVal for next check
                    winVal = 0;
                }


                //check vertical rows
                for (int y = 0; y < 4; ++y)
                {
                    for (int x = 0; x < 4; ++x)
                    {
                        for (int z = 0; z < 4; ++z)
                        {
                            List<int> tempPoint = new List<int> { x, y, z };
                            int tempIndex = pointToIndex(tempPoint);
                            if (currentCheck.Get(tempIndex) == true)
                            {
                                winVal += 1;
                            }
                        }
                        if (winVal == 4)
                        {
                            //someone has won
                            break;
                        }
                        else
                        {
                            //reset winVal for next check
                            winVal = 0;
                        }
                    }
                }

                if (winVal == 4)
                {
                    //someone has won
                    break;
                }
                else
                {
                    //reset winVal for next check
                    winVal = 0;
                }

                //check sub-board left-right diagonals
                for (int z = 0; z < 4; ++z)
                {
                    for (int x = 0; x < 4; ++x)
                    {
                        int y = x;
                        List<int> tempPoint = new List<int> { x, y, z };
                        int tempIndex = pointToIndex(tempPoint);
                        if (currentCheck.Get(tempIndex) == true)
                        {
                            winVal += 1;
                        }
                    }
                    if (winVal == 4)
                    {
                        //someone has won
                        break;
                    }
                    else
                    {
                        //reset winVal for next check
                        winVal = 0;
                    }
                }

                if (winVal == 4)
                {
                    //someone has won
                    break;
                }
                else
                {
                    //reset winVal for next check
                    winVal = 0;
                }

                //check sub-board right-left diagonals
                for (int z = 0; z < 4; ++z)
                {
                    for (int x = 0; x < 4; ++x)
                    {
                        int y = 3 - x;
                        List<int> tempPoint = new List<int> { x, y, z };
                        int tempIndex = pointToIndex(tempPoint);
                        if (currentCheck.Get(tempIndex) == true)
                        {
                            winVal += 1;
                        }
                    }
                    if (winVal == 4)
                    {
                        //someone has won
                        break;
                    }
                    else
                    {
                        //reset winVal for next check
                        winVal = 0;
                    }
                }

                if (winVal == 4)
                {
                    //someone has won
                    break;
                }
                else
                {
                    //reset winVal for next check
                    winVal = 0;
                }


                //check vertical left-right diagonals
                for (int z = 0; z < 4; ++z)
                {
                    int x = z;
                    int y = z;
                    List<int> tempPoint = new List<int> { x, y, z };
                    int tempIndex = pointToIndex(tempPoint);
                    if (currentCheck.Get(tempIndex) == true)
                    {
                        winVal += 1;
                    }
                }

                if (winVal == 4)
                {
                    //someone has won
                    break;
                }
                else
                {
                    //reset winVal for next check
                    winVal = 0;
                }

                //check vertical right-left diagonals
                for (int z = 3; z >= 0; --z)
                {
                    int y = z;
                    int x = 3 - z;
                    List<int> tempPoint = new List<int> { x, y, z };
                    int tempIndex = pointToIndex(tempPoint);
                    if (currentCheck.Get(tempIndex) == true)
                    {
                        winVal += 1;
                    }
                }

                if (winVal == 4)
                {
                    //someone has won
                    break;
                }
                else
                {
                    //reset winVal for next check
                    winVal = 0;
                }



                check = false;
            }//end of checks


           

            if (winVal == 4)
            {
                if (player)
                {
                    //player won
                    winner = 1;
                }
                else
                {
                    //comp won
                    winner = 2;
                }
            }
           
            //else no winner



            return winner;
        }
        /// <summary>
        /// ///////////////////////////////////////////////////
        /// </summary>
        /// <returns></returns>

        public static List<int> CheckXO(bool player, BitArray cGame, BitArray pGame)
        {
            List<int> data = new List<int>(4);

            //check for player/comp win
            BitArray currentCheck = new BitArray(64);

            // Checking player
            if (player)
            {
                currentCheck = pGame;
            }
            //otherwise checking computer
            else
            {
                currentCheck = cGame;
            }

            int count = 0;

            // Variables to keep track of how many 
            int count1 = 0;
            int count2 = 0;
            int count3 = 0;
            int count4 = 0;

            bool check = true;
            while (check)                                     //FIXME: Might not need this while
            {
                //check columns on each sub-board
                for (int z = 0; z < 4; ++z)
                {
                    for (int x = 0; x < 4; ++x)
                    {
                        for (int y = 0; y < 4; ++y)
                        {
                            List<int> tempPoint = new List<int> { x, y, z };
                            int tempIndex = pointToIndex(tempPoint);
                            if (currentCheck.Get(tempIndex) == true)
                            {
                                count += 1;
                            }
                        }

                        if (count == 1)
                        {
                            count1++;
                        }
                        else if (count == 2)
                        {
                            count2++;
                        }
                        else if (count == 3)
                        {
                            count3++;
                        }
                        else if (count == 4)
                        {
                            count4++;
                        }
                        else
                        {
                            //reset count for next check
                            count = 0;
                        }
                    }
                }

                // reset count for next check
                count = 0;

                //check vertical columns
                for (int x = 0; x < 4; ++x)
                {
                    for (int y = 0; y < 4; ++y)
                    {
                        for (int z = 0; z < 4; ++z)
                        {
                            List<int> tempPoint = new List<int> { x, y, z };
                            int tempIndex = pointToIndex(tempPoint);
                            if (currentCheck.Get(tempIndex) == true)
                            {
                                count += 1;
                            }
                        }

                        if (count == 1)
                        {
                            count1++;
                        }
                        else if (count == 2)
                        {
                            count2++;
                        }
                        else if (count == 3)
                        {
                            count3++;
                        }
                        else if (count == 4)
                        {
                            count4++;
                        }
                        else
                        {
                            //reset count for next check
                            count = 0;
                        }
                    }
                }

                // reset count for next check
                count = 0;

                //check rows on each sub-board
                for (int z = 0; z < 4; ++z)
                {
                    for (int y = 0; y < 4; ++y)
                    {
                        for (int x = 0; x < 4; ++x)
                        {
                            List<int> tempPoint = new List<int> { x, y, z };
                            int tempIndex = pointToIndex(tempPoint);
                            if (currentCheck.Get(tempIndex) == true)
                            {
                                count += 1;
                            }
                        }

                        if (count == 1)
                        {
                            count1++;
                        }
                        else if (count == 2)
                        {
                            count2++;
                        }
                        else if (count == 3)
                        {
                            count3++;
                        }
                        else if (count == 4)
                        {
                            count4++;
                        }
                        else
                        {
                            //reset count for next check
                            count = 0;
                        }
                    }
                }

                // reset count for next check
                count = 0;

                //check vertical rows
                for (int y = 0; y < 4; ++y)
                {
                    for (int x = 0; x < 4; ++x)
                    {
                        for (int z = 0; z < 4; ++z)
                        {
                            List<int> tempPoint = new List<int> { x, y, z };
                            int tempIndex = pointToIndex(tempPoint);
                            if (currentCheck.Get(tempIndex) == true)
                            {
                                count += 1;
                            }
                        }

                        if (count == 1)
                        {
                            count1++;
                        }
                        else if (count == 2)
                        {
                            count2++;
                        }
                        else if (count == 3)
                        {
                            count3++;
                        }
                        else if (count == 4)
                        {
                            count4++;
                        }
                        else
                        {
                            //reset count for next check
                            count = 0;
                        }
                    }
                }

                // reset count for next check
                count = 0;

                //check sub-board left-right diagonals
                for (int z = 0; z < 4; ++z)
                {
                    for (int x = 0; x < 4; ++x)
                    {
                        int y = x;
                        List<int> tempPoint = new List<int> { x, y, z };
                        int tempIndex = pointToIndex(tempPoint);
                        if (currentCheck.Get(tempIndex) == true)
                        {
                            count += 1;
                        }
                    }

                    if (count == 1)
                    {
                        count1++;
                    }
                    else if (count == 2)
                    {
                        count2++;
                    }
                    else if (count == 3)
                    {
                        count3++;
                    }
                    else if (count == 4)
                    {
                        count4++;
                    }
                    else
                    {
                        //reset count for next check
                        count = 0;
                    }
                }

                // reset count for next check
                count = 0;

                //check sub-board right-left diagonals
                for (int z = 0; z < 4; ++z)
                {
                    for (int x = 0; x < 4; ++x)
                    {
                        int y = 3 - x;
                        List<int> tempPoint = new List<int> { x, y, z };
                        int tempIndex = pointToIndex(tempPoint);
                        if (currentCheck.Get(tempIndex) == true)
                        {
                            count += 1;
                        }
                    }

                    if (count == 1)
                    {
                        count1++;
                    }
                    else if (count == 2)
                    {
                        count2++;
                    }
                    else if (count == 3)
                    {
                        count3++;
                    }
                    else if (count == 4)
                    {
                        count4++;
                    }
                    else
                    {
                        //reset count for next check
                        count = 0;
                    }
                }

                // reset count for next check
                count = 0;

                //check vertical left-right diagonals
                for (int z = 0; z < 4; ++z)
                {
                    int x = z;
                    int y = z;
                    List<int> tempPoint = new List<int> { x, y, z };
                    int tempIndex = pointToIndex(tempPoint);
                    if (currentCheck.Get(tempIndex) == true)
                    {
                        count += 1;
                    }
                }

                if (count == 1)
                {
                    count1++;
                }
                else if (count == 2)
                {
                    count2++;
                }
                else if (count == 3)
                {
                    count3++;
                }
                else if (count == 4)
                {
                    count4++;
                }
                else
                {
                    //reset count for next check
                    count = 0;
                }

                // reset count for next check
                count = 0;
                //check vertical right-left diagonals
                for (int z = 3; z >= 0; --z)
                {
                    int y = z;
                    int x = 3 - z;
                    List<int> tempPoint = new List<int> { x, y, z };
                    int tempIndex = pointToIndex(tempPoint);
                    if (currentCheck.Get(tempIndex) == true)
                    {
                        count += 1;
                    }
                }

                if (count == 1)
                {
                    count1++;
                }
                else if (count == 2)
                {
                    count2++;
                }
                else if (count == 3)
                {
                    count3++;
                }
                else if (count == 4)
                {
                    count4++;
                }
                else
                {
                    //reset count for next check
                    count = 0;
                }

                check = false;
            } //end of checks


            //BitArray checker = new BitArray(64);
            //checker.SetAll(true);
           data.Insert(0, count1);
           data.Insert(1, count2);
           data.Insert(2, count3);
           data.Insert(3, count4);

            return data;
        }

        /////////////////////////////////////////////////////////////
        public static int BestMoveFinder()
        {
            //////////////////IS THIS EVEN ACCURATE? !
            GlobalClass.board = new BitArray(GlobalClass.pGame);
            GlobalClass.board.Or(GlobalClass.cGame);
            //Console.WriteLine("LOOK HERE, FIX ME: " + GlobalClass.board.Get(0));
            //Console.WriteLine("LOOK HERE, FIX ME: " + GlobalClass.board.Get(35));
            BitArray p = new BitArray(GlobalClass.pGame);
            BitArray c = new BitArray(GlobalClass.cGame);

            //////////////////////? ? ? ? ??  ? ?
            int bestMove = int.MinValue;

            int bestMoveAI = -1;
            //call minimax on all possible moves
            for (int i = 0; i < 64; i++)
            {
                if (!GlobalClass.board.Get(i))
                {
                    c.Set(i, true);
                    int move = GlobalClass.Minimax(p, c, 0, false, GlobalClass.MIN, GlobalClass.MAX);
                    c.Set(i, false);
                    if (move > bestMove)
                    {
                        bestMove = move;
                        bestMoveAI = i;
                    }
                }
            }
            //cout << bestMove <<endl;
            return bestMoveAI;// bit that needs to be updated
        }

        /// <summary>
        /// //////////////////////////////////////////////////
        /// </summary>
        /// <returns></returns>
        public static int Minimax(BitArray pGame, BitArray cGame, int level, bool isComp, int alpha, int beta)
        {
            //////////////////////////// IS THIS EVEN ACCURATE?
            //BitArray tempPGame = new BitArray(pGame);
            //tempPGame.Or(cGame);
            BitArray tempPGame = new BitArray(GlobalClass.pGame);
            tempPGame.Or(GlobalClass.cGame);

            //BitArray pGameCopy = new BitArray(pGame);
            //BitArray cGameCopy = new BitArray(cGame);
            //ulong pUintCopy = GlobalClass.GetIntFromBitArray(pGame); 
            //ulong cUintCopy = GlobalClass.GetIntFromBitArray(cGame);

            //pUintCopy = GlobalClass.GetIntFromBitArray(pGameCopy);
            //cUintCopy = GlobalClass.GetIntFromBitArray(cGameCopy);
            

            //cut off condition
            if (level == GlobalClass.DEPTH_MAX)
            {
                return GlobalClass.UtilityFunction(cGame, pGame);
            }
            //if x won
            if (GlobalClass.Winner(true, pGame) == 1)
            {

                return GlobalClass.UtilityFunction(cGame, pGame);
            }
            //if o won
            if (GlobalClass.Winner(false, cGame) == 2)
            {
                return GlobalClass.UtilityFunction(cGame, pGame);
            }
            //////////////////////////NO IDEA HOW TO DO THIS IN C#
            //if no available spots left
            /*if (board.all())
            {
                return 0;
            }*/
            var anyTrue = tempPGame.Cast<bool>().Any(x => x);
            if (!anyTrue)
            {
                return 0;
            }

            //maximizing
            if (isComp)
            {
                /*****************************************/
                int bestMove = int.MinValue;

                for (int i = 0; i < 64; i++)
                {
                    // Not sure if this will work though
                    if (!tempPGame.Get(i))
                    {
                    
                        cGame.Set(i, true);
                        bestMove = Max(bestMove, GlobalClass.Minimax(pGame, cGame, level + 1, !isComp, alpha, beta));
                        alpha = Max(alpha, bestMove);
                        if (beta <= alpha)
                        {
                            break;
                        }
                        cGame.Set(i, false);
                    }
                }
                return bestMove;
            }
            else
            {
                //minimizing
                int bestMove = int.MaxValue;

                for (int i = 0; i < 64; i++)
                {
                    if (!tempPGame.Get(i))
                    {
                        pGame.Set(i, true);
                        bestMove = Min(bestMove, GlobalClass.Minimax(pGame, cGame, level + 1, !isComp, alpha, beta));
                        beta = Min(beta, bestMove);
                        if (beta <= alpha)
                        {
                            break;
                        }
                        pGame.Set(i, false);
                    }
                }
                return bestMove;
            }
        }
/// <summary>
/// ///////////////////
        public static int UtilityFunction(BitArray comGame, BitArray playGame) 
        {
            GlobalClass.dataX = GlobalClass.CheckXO(true, comGame, playGame);
            GlobalClass.dataO = GlobalClass.CheckXO(false, comGame, playGame);

            int ans = 1000 * (GlobalClass.dataX[3] - GlobalClass.dataO[3])
                    + 100 * (GlobalClass.dataX[2] - GlobalClass.dataO[2])
                    + 10 * (GlobalClass.dataX[1] - GlobalClass.dataO[1])
                    + (GlobalClass.dataX[0] - GlobalClass.dataO[0]);

            return ans;
        }
    }
}
