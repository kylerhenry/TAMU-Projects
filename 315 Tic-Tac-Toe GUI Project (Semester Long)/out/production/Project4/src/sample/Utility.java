package sample;

import java.util.ArrayList;
import java.util.Arrays;

public class Utility {

    private class Square{
        boolean checked = false;
        int val = 0;
    }

    private class Coordinate{
        short x  = 0;
        short y =  0;
        short z = 0;
        ArrayList<Integer> diagDirections = new ArrayList<>();
    }

    void findDirection(ArrayList<Integer> diagDirections, int i, int j, int k){
        if(i == j)
            diagDirections.add(1);
        else if(i == 3 - j)
            diagDirections.add(2);

        if((k == 0 && i == 0) || (k == 1 && i == 1) || (k == 2 && i == 2) || (k == 3 && i == 3)){
            diagDirections.add(3);
        }
        else if((k == 0 && i == 3) || (k == 1 && i == 2) || (k == 2 && i == 1) || (k == 3 && i ==0)){
            diagDirections.add(4);
        }

        if((k == 0 && j == 0) || (k == 1 && j == 1) || (k == 2 && j == 2) || (k == 3 && j == 3)){
            diagDirections.add(5);
        }
        else if((k == 0 && j == 3) || (k == 1 && j == 2) || (k == 2 && j == 1) || (k == 3 && j == 0)){
            diagDirections.add(6);
        }

        if((i == j) && (k == i)){
            diagDirections.add(7);
        }
        else if((i == j) && (k == 3 - i)){
            diagDirections.add(8);
        }
        else if((i == 3 - j) && (k == i)){
            diagDirections.add(9);
        }
        else if((i == 3 -j) && (k == 3 - i)){
            diagDirections.add(10);
        }
    }

    void populateBoard(ArrayList<ArrayList<ArrayList<Square>>> board, long b, ArrayList<Coordinate> XSquares){
        long temp = 0;
        for(int k = 3; k >= 0; k--){
            for(int i = 3; i >= 0; i--){
                ArrayList<Square> row = new ArrayList<Square>(4);
                row.add(new Square());
                row.add(new Square());
                row.add(new Square());
                row.add(new Square());

                for(int j = 3; j >= 0; j--){
                    Square s = new Square();
                    temp = b & 1;
                    if(temp == 1){
                        Coordinate coord = new Coordinate();
                        coord.x = (short) i;
                        coord.y = (short) j;
                        coord.z = (short) k;
                        findDirection(coord.diagDirections, i, j, k);
                        s.val = 1;
                        XSquares.add(coord);
                    }
                    row.set(j,s);
                    b >>= 1;
                }
                board.get(k).set(i,row);
            }
        }
    }

    int leftXCount(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentColumn = col - 1;

        while(currentColumn >= 0){
            if(v.get(lvl).get(row).get(currentColumn).val == 1){
                if(v.get(lvl).get(row).get(currentColumn).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentColumn--;
        }
        return count;
    }

    int rightXCount(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentColumn = col + 1;

        while(currentColumn < 4){
            if(v.get(lvl).get(row).get(currentColumn).val == 1){
                if(v.get(lvl).get(row).get(currentColumn).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentColumn++;
        }
        return count;
    }

    int leftRightXCount(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int left = leftXCount(v, row, col, lvl);
        int right = rightXCount(v, row, col, lvl);

        if(left == -1 || right == -1){
            return -1;
        }
        else{
            return left + right + 1;
        }
    }

    //Rows vertical to the computer screen
//ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl

    int upXCount(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentRow = row - 1;

        while(currentRow >= 0){
            if(v.get(lvl).get(currentRow).get(col).val == 1){
                if(v.get(lvl).get(currentRow).get(col).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentRow--;
        }
        return count;
    }

    int downXCount(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentRow = row + 1;

        while(currentRow < 4){
            if(v.get(lvl).get(currentRow).get(col).val == 1){
                if(v.get(lvl).get(currentRow).get(col).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentRow++;
        }
        return count;
    }


    int upDownXCount(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int up = upXCount(v, row, col, lvl);
        int down = downXCount(v, row, col, lvl);

        if(up == -1 || down == -1){
            return -1;
        }
        else{
            return up + down + 1;
        }
    }


    //Rows coming out of the computer screen
    int frontXCount(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentLvl = lvl - 1;

        while(currentLvl >= 0){
            if(v.get(currentLvl).get(row).get(col).val == 1){
                if(v.get(currentLvl).get(row).get(col).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentLvl--;
        }
        return count;
    }

    int backXCount(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentLvl = lvl + 1;

        while(currentLvl < 4){
            if(v.get(currentLvl).get(row).get(col).val == 1){
                if(v.get(currentLvl).get(row).get(col).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentLvl++;
        }
        return count;
    }

    int frontBackXCount(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int front = frontXCount(v, row, col, lvl);
        int back = backXCount(v, row, col, lvl);

        if(front == -1 || back == -1){
            return -1;
        }
        else{
            return front + back + 1;
        }
    }

    int diagFlat1Left(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentRow = row - 1;
        int currentColumn = col - 1;

        while(currentRow >= 0){
            if(v.get(lvl).get(currentRow).get(currentColumn).val == 1){
                if(v.get(lvl).get(currentRow).get(currentColumn).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentRow--;
            currentColumn--;
        }
        return count;
    }


    int diagFlat1Right(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentRow = row + 1;
        int currentColumn = col + 1;

        while(currentRow < 4){
            if(v.get(lvl).get(currentRow).get(currentColumn).val == 1){
                if(v.get(lvl).get(currentRow).get(currentColumn).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentRow++;
            currentColumn++;
        }
        return count;
    }


    int diagFlat1(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int left = diagFlat1Left(v, row, col, lvl);
        int right = diagFlat1Right(v, row, col, lvl);

        if(left == -1 || right == -1){
            return -1;
        }
        else{
            return left + right + 1;
        }
    }

    int diagFlat2Left(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentRow = row + 1;
        int currentColumn = col - 1;

        while(currentRow < 4){
            if(v.get(lvl).get(currentRow).get(currentColumn).val == 1){
                if(v.get(lvl).get(currentRow).get(currentColumn).checked== true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentRow++;
            currentColumn--;
        }
        return count;
    }

    int diagFlat2Right(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentRow = row - 1;
        int currentColumn = col + 1;

        while(currentRow >= 0){
            if(v.get(lvl).get(currentRow).get(currentColumn).val == 1){
                if(v.get(lvl).get(currentRow).get(currentColumn).checked== true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentRow--;
            currentColumn++;
        }
        return count;
    }

    int diagFlat2(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int left = diagFlat2Left(v, row, col, lvl);
        int right = diagFlat2Right(v, row, col, lvl);

        if(left == -1 || right == -1){
            return -1;
        }
        else{
            return left + right + 1;
        }
    }

    //Up Down
    int diagUpDown1Top(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentRow = row - 1;
        int currentLvl = lvl - 1;

        while(currentRow >= 0){
            if(v.get(currentLvl).get(currentRow).get(col).val == 1){
                if(v.get(currentLvl).get(currentRow).get(col).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentRow--;
            currentLvl--;
        }
        return count;
    }

    int diagUpDown1Bottom(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentRow = row + 1;
        int currentLvl = lvl + 1;

        while(currentRow < 4){
            if(v.get(currentLvl).get(currentRow).get(col).val == 1){
                if(v.get(currentLvl).get(currentRow).get(col).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentRow++;
            currentLvl++;
        }
        return count;
    }

    int diagUpDown1(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int top = diagUpDown1Top(v, row, col, lvl);
        int bottom = diagUpDown1Bottom(v, row, col, lvl);
        if(top == -1 || bottom == -1){
            return -1;
        }
        else{
            return top + bottom + 1;
        }
    }

    int diagUpDown2Top(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentRow = row + 1;
        int currentLvl = lvl - 1;

        while(currentRow < 4){
            if(v.get(currentLvl).get(currentRow).get(col).val == 1){
                if(v.get(currentLvl).get(currentRow).get(col).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentRow++;
            currentLvl--;
        }
        return count;
    }

    int diagUpDown2Bottom(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentRow = row - 1;
        int currentLvl = lvl + 1;

        while(currentRow >=0){
            if(v.get(currentLvl).get(currentRow).get(col).val == 1){
                if(v.get(currentLvl).get(currentRow).get(col).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentRow--;
            currentLvl++;
        }
        return count;
    }

    int diagUpDown2(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int top = diagUpDown2Top(v, row, col, lvl);
        int bottom = diagUpDown2Bottom(v, row, col, lvl);

        if(top == -1 || bottom == -1){
            return -1;
        }
        else{
            return top + bottom + 1;
        }
    }

    int diagLeftRight1Left(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentColumn = col - 1;
        int currentLvl = lvl - 1;

        while(currentColumn >= 0){
            if(v.get(currentLvl).get(row).get(currentColumn).val == 1){
                if(v.get(currentLvl).get(row).get(currentColumn).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentColumn--;
            currentLvl--;
        }
        return count;
    }

    int diagLeftRight1Right(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentColumn = col + 1;
        int currentLvl = lvl + 1;

        while(currentColumn < 4){
            if(v.get(currentLvl).get(row).get(currentColumn).val == 1){
                if(v.get(currentLvl).get(row).get(currentColumn).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentColumn++;
            currentLvl++;
        }
        return count;
    }

    int diagLeftRight1(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int left = diagLeftRight1Left(v, row, col, lvl);
        int right = diagLeftRight1Right(v, row, col, lvl);

        if(left == -1 || right == -1){
            return -1;
        }
        else{
            return left + right + 1;
        }
    }

    int diagLeftRight2Left(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentColumn = col - 1;
        int currentLvl = lvl + 1;

        while(currentColumn >= 0){
            if(v.get(currentLvl).get(row).get(currentColumn).val == 1){
                if(v.get(currentLvl).get(row).get(currentColumn).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentColumn--;
            currentLvl++;
        }
        return count;
    }

    int diagLeftRight2Right(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentColumn = col + 1;
        int currentLvl = lvl - 1;

        while(currentColumn < 4){
            if(v.get(currentLvl).get(row).get(currentColumn).val == 1){
                if(v.get(currentLvl).get(row).get(currentColumn).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentColumn++;
            currentLvl--;
        }
        return count;
    }

    int diagLeftRight2(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int left = diagLeftRight2Left(v, row, col, lvl);
        int right = diagLeftRight2Right(v, row, col, lvl);

        if(left == -1 || right == -1){
            return -1;
        }
        else{
            return left + right + 1;
        }
    }

    //Diagonals that touch the cornors of the 3D board
    int diagCorners1Left(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentRow = row - 1;
        int currentColumn = col - 1;
        int currentLvl = lvl - 1;

        while(currentColumn >= 0){
            if(v.get(currentLvl).get(currentRow).get(currentColumn).val == 1){
                if(v.get(currentLvl).get(currentRow).get(currentColumn).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentRow--;
            currentColumn--;
            currentLvl--;
        }
        return count;
    }

    int diagCorners1Right(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentRow = row + 1;
        int currentColumn = col + 1;
        int currentLvl = lvl + 1;

        while(currentColumn < 4){
            if(v.get(currentLvl).get(currentRow).get(currentColumn).val == 1){
                if(v.get(currentLvl).get(currentRow).get(currentColumn).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentRow++;
            currentColumn++;
            currentLvl++;
        }
        return count;
    }

    int diagCorners1(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int left = diagCorners1Left(v, row, col, lvl);
        int right = diagCorners1Right(v, row, col, lvl);

        if(left == -1 || right == -1){
            return -1;
        }
        else{
            return left + right + 1;
        }
    }

    int diagCorners2Left(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentRow = row - 1;
        int currentColumn = col - 1;
        int currentLvl = lvl + 1;

        while(currentColumn >= 0){
            if(v.get(currentLvl).get(currentRow).get(currentColumn).val == 1){
                if(v.get(currentLvl).get(currentRow).get(currentColumn).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentRow--;
            currentColumn--;
            currentLvl++;
        }
        return count;
    }

    int diagCorners2Right(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentRow = row + 1;
        int currentColumn = col + 1;
        int currentLvl = lvl - 1;

        while(currentColumn < 4){
            if(v.get(currentLvl).get(currentRow).get(currentColumn).val == 1){
                if(v.get(currentLvl).get(currentRow).get(currentColumn).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentRow++;
            currentColumn++;
            currentLvl--;
        }
        return count;
    }

    int diagCorners2(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int left = diagCorners2Left(v, row, col, lvl);
        int right = diagCorners2Right(v, row, col, lvl);

        if(left == -1 || right == -1){
            return -1;
        }
        else{
            return left + right + 1;
        }
    }

    int diagCorners3Left(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentRow = row + 1;
        int currentColumn = col - 1;
        int currentLvl = lvl + 1;

        while(currentColumn >= 0){
            if(v.get(currentLvl).get(currentRow).get(currentColumn).val == 1){
                if(v.get(currentLvl).get(currentRow).get(currentColumn).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentRow++;
            currentColumn--;
            currentLvl++;
        }
        return count;
    }

    int diagCorners3Right(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentRow = row - 1;
        int currentColumn = col + 1;
        int currentLvl = lvl - 1;

        while(currentColumn < 4){
            if(v.get(currentLvl).get(currentRow).get(currentColumn).val == 1){
                if(v.get(currentLvl).get(currentRow).get(currentColumn).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentRow--;
            currentColumn++;
            currentLvl--;
        }
        return count;
    }

    int diagCorners3(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int left = diagCorners3Left(v, row, col, lvl);
        int right = diagCorners3Right(v, row, col, lvl);

        if(left == -1 || right == -1){
            return -1;
        }
        else{
            return left + right + 1;
        }
    }

    int diagCorners4Left(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentRow = row + 1;
        int currentColumn = col - 1;
        int currentLvl = lvl - 1;

        while(currentColumn >= 0){
            if(v.get(currentLvl).get(currentRow).get(currentColumn).val == 1){
                if(v.get(currentLvl).get(currentRow).get(currentColumn).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentRow++;
            currentColumn--;
            currentLvl--;
        }
        return count;
    }

    int diagCorners4Right(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int count = 0;
        int currentRow = row - 1;
        int currentColumn = col + 1;
        int currentLvl = lvl + 1;

        while(currentColumn < 4){
            if(v.get(currentLvl).get(currentRow).get(currentColumn).val == 1){
                if(v.get(currentLvl).get(currentRow).get(currentColumn).checked == true){
                    return -1;
                }
                else{
                    count++;
                }
            }
            currentRow--;
            currentColumn++;
            currentLvl++;
        }
        return count;
    }

    int diagCorners4(ArrayList<ArrayList<ArrayList<Square>>> v, short row, short col, short lvl){
        int left = diagCorners4Left(v, row, col, lvl);
        int right = diagCorners4Right(v, row, col, lvl);

        if(left == -1 || right == -1){
            return -1;
        }
        else{
            return left + right + 1;
        }
    }

    //utility helper functions
    int getDcount(int dir, ArrayList<Coordinate> Squares, ArrayList<ArrayList<ArrayList<Square>>> board, int i, int j){

        switch(Squares.get(i).diagDirections.get(j)){
            case 1:
                return diagFlat1(board, Squares.get(i).x, Squares.get(i).y, Squares.get(i).z);
            case 2:
                return diagFlat2(board, Squares.get(i).x, Squares.get(i).y, Squares.get(i).z);
            case 3:
                return diagUpDown1(board, Squares.get(i).x, Squares.get(i).y, Squares.get(i).z);
            case 4:
                return diagUpDown2(board, Squares.get(i).x, Squares.get(i).y, Squares.get(i).z);
            case 5:
                return diagLeftRight1(board, Squares.get(i).x, Squares.get(i).y, Squares.get(i).z);
            case 6:
                return diagLeftRight2(board, Squares.get(i).x, Squares.get(i).y, Squares.get(i).z);
            case 7:
                return diagCorners1(board, Squares.get(i).x, Squares.get(i).y, Squares.get(i).z);
            case 8:
                return diagCorners2(board, Squares.get(i).x, Squares.get(i).y, Squares.get(i).z);
            case 9:
                return diagCorners3(board, Squares.get(i).x, Squares.get(i).y, Squares.get(i).z);
            case 10:
                return diagCorners4(board, Squares.get(i).x, Squares.get(i).y, Squares.get(i).z);
            default:
                return 0;
        }
    }

    void FindInARow(ArrayList<Integer> data, long b){
        data.add(new Integer(0));
        data.add(new Integer(0));
        data.add(new Integer(0));
        data.add(new Integer(0));
        ArrayList<Coordinate> Squares = new ArrayList<>();
        ArrayList<ArrayList<ArrayList<Square>>> board = new ArrayList<>();
        for(int i = 0 ; i < 4; i++){
            board.add(new ArrayList<>());
            for(int j = 0; j < 4; j++){
                board.get(i).add(new ArrayList<>());
                for(int k = 0; k <4; k ++){
                    board.get(i).get(j).add(k, new Square());
                }
            }
        }
        //populate the entire board with bits from b
        populateBoard(board, b, Squares);
        int LRcount, UDcount, FBcount, Dcount = 0;

        for(int i = 0; i < Squares.size(); i++){
            board.get(Squares.get(i).z).get(Squares.get(i).x).get(Squares.get(i).y).checked = true;
            LRcount = leftRightXCount(board, Squares.get(i).x, Squares.get(i).y, Squares.get(i).z);
            UDcount = upDownXCount(board, Squares.get(i).x, Squares.get(i).y, Squares.get(i).z);
            FBcount = frontBackXCount(board, Squares.get(i).x, Squares.get(i).y, Squares.get(i).z);

            for(int j = 0; j < Squares.get(i).diagDirections.size(); j++){
                Dcount = getDcount(Squares.get(i).diagDirections.get(j), Squares, board, i, j);
                if(Dcount != -1 && Dcount != 0){
                    //System.out.println(data) ;
                    data.set(Dcount - 1, data.get(Dcount - 1) +1);
                }
                //System.out.println(Dcount);
            }

            if(LRcount != -1){
                data.set(LRcount - 1, data.get(LRcount - 1)+1);
            }
            if(UDcount != -1){
                data.set(UDcount - 1, data.get(UDcount - 1)+1);
            }
            if(FBcount != -1){
                data.set(FBcount - 1 , data.get(FBcount - 1)+1);
            }
        }
        //for debugging purposes

//        System.out.println("Number of One X's in a row: " + data.get(0));
//        System.out.println("Number of Two's X's in a row: " + data.get(1));
//        System.out.println("Number of Three X's in a row: " + data.get(2));
//        System.out.println("Number of Four X's in a row: " + data.get(3));

    }

    int utilityFunction(long Xs, long Os){
        ArrayList<Integer> dataX = new ArrayList<Integer>(4);
        ArrayList<Integer> dataO = new ArrayList<Integer>(4);
        long xs = new Long(Xs);
        long os = new Long(Os);

        FindInARow(dataX, xs);
        FindInARow(dataO, os);

        int ans = 1000 * (dataX.get(3) - dataO.get(3))
                + 100  * (dataX.get(2) - dataO.get(2))
                + 10   * (dataX.get(1) - dataO.get(1))
                +        (dataX.get(0) - dataO.get(0));

        return ans;
    }

    int Winner(long Xs, long Os){
        //return (1) X wins (2) O wins (3) No one wins (4)
        ArrayList<Integer> dataX = new ArrayList<Integer>(4);
        ArrayList<Integer> dataO = new ArrayList<Integer>(4);

        FindInARow(dataX, Xs);
        FindInARow(dataO, Os);

        if(dataX.get(3) > 0)
            return 1;
        else if(dataO.get(3) > 0)
            return 2;
        else if((Xs | Os ) == -1 )
            return 3;
        else
            return 4;
    }

}

