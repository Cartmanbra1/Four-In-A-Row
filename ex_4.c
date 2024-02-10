// (89110, Spring 2023, Assignment #4, Roie Amsalem, 322535436, roieams)
#include "ex_4.h"

char Base64(char countToChar);

/**
 * @brief Initializes the game board with empty spaces.
 *
 * This function sets all elements of the game board to a space character (' ').
 *
 * @param board The game board.
 * @param rows The number of rows in the game board.
 * @param columns The number of columns in the game board.
 */
void initBoard(char board[ROWS][COLS], int rows, int columns) {
    int i, j;
    // Iterate over each row top to bottom.
    for (i = 0; i <= rows; i++) {
        // Iterate over each column left to right.
        for (j = 0; j < columns; j++) {
            // Set the element to an empty space character.
            board[i][j] = ' ';
        }
    }
}

/**
 * @brief Prints the game board.
 *
 * This function prints the current state of the game board, including the borders.
 * It uses '|' to separate columns and '~' to represent the borders.
 *
 * @param board The game board.
 * @param rows The number of rows in the game board.
 * @param columns The number of columns in the game board.
 */
void printBoard(char board[ROWS][COLS], int rows, int columns) {
    int i, j;
    // Iterate over each row, including the borders, top to bottom.
    for (i = -1; i < rows + 1; i++) {
        // Iterate over each column
        for (j = 0; j < columns; j++) {
            // Check if the current row is a border row.
            if (i == -1 || i == rows) {
                // Print horizontal border.
                if (j == columns - 1) {
                    printf("~~~");
                } else {
                    printf("~~");
                }
            } else {
                // Print the element and vertical border.
                printf("|%c", board[i][j]);
                if (j == columns - 1) {
                    // Print the last rightmost border.
                    printf("|");
                }
            }
        }
        printf("\n");
    }
}

/**
 * @brief Makes a move on the game board.
 *
 * This function places a player's piece on the specified column of the game board.
 *
 * @param board The game board.
 * @param rows The number of rows in the game board.
 * @param columns The number of columns in the game board.
 * @param players The number of players.
 * @param player The current player's piece.
 * @param column The column where the move is made.
 * @return 1 if the move was successful, 0 otherwise.
 */
int makeMove(char board[ROWS][COLS], int rows, int columns, int players, char player, int column) {
    int j = column;
    //Checking if the move is within bounds.
    if (column >= columns) {
        return 0;
    }
    // Check if the amount of players doesn't cross the allowed number.
    if (player < 'A' || player >= ('A' + players)) {
        return 0;
    }
    // Iterate over the rows starting from the bottom.
    for (int i = rows - 1; i >= 0; i--) {
        // Check if the current position is already occupied by a player's piece
        if (board[i][j] >= 'A' && board[i][j] <= 'Z') {
            // Skip to the next row if the current row is already full
            continue;
        } else {
            board[i][j] = player;
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Undoes a move on the game board.
 *
 * This function removes the top piece from the specified column of the game board.
 *
 * @param board The game board.
 * @param rows The number of rows in the game board.
 * @param columns The number of columns in the game board.
 * @param column The column where the move is undone.
 * @return 1 if the undo was successful, 0 otherwise.
 */
int undoMove(char board[ROWS][COLS], int rows, int columns, int column) {
    int j = column;
    //Checking if the undo is within bounds.
    if (column >= columns) {
        return 0;
    }
    // Iterate over the rows.
    for (int i = 0; i < rows; ++i) {
        // Check if the current position is occupied by a player's piece.
        if (board[i][j] >= 'A' && board[i][j] <= 'Z') {
            // Undo the move by setting the position back to empty.
            board[i][j] = ' ';
            // Move successfully undone.
            return 1;
        } else {
            // Continue to the next row if the current row is empty.
            continue;
        }
    }
    // No move to undo, column is empty.
    return 0;
}

/**
 * @brief Gets the current status of the game.
 *
 * This function checks if any player has won the game or if it is still ongoing.
 *
 * @param board The game board.
 * @param rows The number of rows in the game board.
 * @param columns The number of columns in the game board.
 * @param players The number of players.
 * @param connect The number of pieces required to win.
 * @return 1 if a player has won, 0 if the game is still ongoing, -1 if the game is a draw.
 */
int getStatus(char board[ROWS][COLS], int rows, int columns, __attribute__((__unused__)) int players, int connect) {
    int countRow = 0, countCol = 0, countDiagonal = 0;
    // Check for horizontal connect.
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            // Check if the current position is occupied by a player's piece.
            if (board[i][j] >= 'A' && board[i][j] <= 'Z') {
                // Check if there is a horizontal connect starting from the current position.
                if (board[i][j] == board[i][j + 1] && (j + 1) < columns) {
                    countRow++;
                    if (countRow == connect - 1) {
                        // Horizontal connect found.
                        return 1;
                    }
                } else {
                    // Reset the count if the connect is broken.
                    countRow = 0;
                }
            }
        }
    }
    // Check for vertical connect.
    for (int j = 0; j < columns; j++) {
        for (int i = 0; i < rows; i++) {
            // Check if the current position is occupied by a player's piece.
            if (board[i][j] >= 'A' && board[i][j] <= 'Z') {
                // Check if there is a vertical connect starting from the current position.
                if (board[i][j] == board[i + 1][j] && (i + 1) < rows) {
                    countCol++;
                    if (countCol == connect - 1) {
                        // Vertical connect found.
                        return 1;
                    }
                } else {
                    // Reset the count if the connect is broken.
                    countCol = 0;
                }
            }
        }
    }
    // Check for diagonal connect.
    for (int j = 0; j < columns; j++) {
        for (int i = (rows - 1); i >= 0; i--) {
            // Check if the current position is occupied by a player's piece.
            if (board[i][j] >= 'A' && board[i][j] <= 'Z') {
                // Check if there is a diagonal connect starting from the current position.
                if (board[i][j] == board[i - 1][j + 1] && (i - 1 >= 0) && (j + 1 < columns)) {
                    countDiagonal++;
                    if (countDiagonal == connect - 1) {
                        // Diagonal connect found.
                        return 1;
                    }
                } else {
                    // Reset the count if the connect is broken.
                    countDiagonal = 0;
                }
            }
        }
    }
    // Iterate through the top row to check if there is room left
    for (int j = 0; j < columns; j++) {
        // If there is 1 element with ' ' in the array, return game in progress.
        if (board[0][j] == ' ') {
            return -1;
        }
    }
    //If we reached here its a tie.
    return 0;
}

/**
 * @brief Gets the winner of the game.
 *
 * This function determines the winner of the game, if any.
 *
 * @param board The game board.
 * @param rows The number of rows in the game board.
 * @param columns The number of columns in the game board.
 * @param players The number of players.
 * @param connect The number of pieces required to win.
 * @return The winning player's piece, or -1 if there is no winner yet.
 */
char getWinner(char board[ROWS][COLS], int rows, int columns, __attribute__((__unused__)) int players, int connect) {
    int countRow = 0, countCol = 0, countDiagonal = 0;
    // Check for horizontal connect
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] >= 'A' && board[i][j] <= 'Z') {
                if (board[i][j] == board[i][j + 1] && (j + 1) < columns) {
                    countRow++;
                    // Horizontal connect found
                    if (countRow == connect - 1) {
                        return board[i][j];
                    }
                } else {
                    // Reset the count if the connect is broken
                    countRow = 0;
                }
            }
        }
    }
    // Check for vertical connect
    for (int j = 0; j < columns; j++) {
        for (int i = 0; i < rows; i++) {
            if (board[i][j] >= 'A' && board[i][j] <= 'Z') {
                if (board[i][j] == board[i + 1][j] && (i + 1) < rows) {
                    countCol++;
                    if (countCol == connect - 1) {
                        // Vertical connect found
                        return board[i][j];
                    }
                } else {
                    // Reset the count if the connect is broken
                    countCol = 0;
                }
            }
        }
    }
    // Check for diagonal connect across columns (iterate all rows each column).
    for (int j = 0; j < columns; j++) {
        for (int i = (rows - 1); i >= 0; i--) {
            if (board[i][j] >= 'A' && board[i][j] <= 'Z') {
                if (board[i][j] == board[i - 1][j + 1] && (i - 1 >= 0) && (j + 1 < columns)) {
                    countDiagonal++;
                    if (countDiagonal == connect - 1) {
                        // Diagonal connect found
                        return board[i][j];
                    }
                } else {
                    // Reset the count if the connect is broken
                    countDiagonal = 0;
                }
            }
        }
    }
    // No winner found
    return -1;
}

/**
 * @brief Checks if the game board is valid.
 *
 * This function checks if the game board is valid, considering the number of players,
 * the number of connect pieces required to win, and the arrangement of pieces on the board.
 *
 * @param board The game board.
 * @param rows The number of rows in the game board.
 * @param columns The number of columns in the game board.
 * @param players The number of players.
 * @param connect The number of pieces required to win.
 * @return 1 if the game board is valid, 0 otherwise.
 */
int playerAmount(char board[ROWS][COLS], int rows, int columns, int players) {
    const int SIZE_OF_A = 'A';
    int countA = 1, countApp = 0;
    char player, lastMove = 'A';
    for (int i = 0; i < players; i++) {
        player = i + SIZE_OF_A;
        countApp = 0;
        for (int j = 0; j < rows; j++) {
            for (int k = 0; k < columns; k++) {
                if ((board[j][k] - SIZE_OF_A) >= players) {
                    return -1;
                } else if (board[j][k] == player) {
                    countApp++;
                }
            }
        }
        if (countA == 1) {
            countA = countApp;
        } else if ((countA > (countApp + 1) || ((countA < countApp) && (countA != countApp + 1)))){
            return -1;
        } else if (countA == countApp){
            lastMove = player;
        }
    }
    return lastMove;
}

int emptyBoard(char board[ROWS][COLS], int rows, int columns){
    const int MAX_ELEMENTS = ((columns - 1) * rows);
    int stopCondCount = 0;
    // Iterate over each row of the game board
    for (int i = 0; i < rows; i++){
        // Iterate over each column of the current row
        for (int j = 0; j < columns; j++){
            // Check if the current cell is equal to the next cell in the same row
            if (board[i][j] == board[i][j+1] && (j + 1 < columns)) {
                // Increment the counter for stop condition check
                stopCondCount++;
            }
        }
    }
    // Check if the stop condition count matches the maximum number of elements on the board
    if (stopCondCount == MAX_ELEMENTS) {
        // The board is valid
        return 1;
    }
}

int checkValidBoard(char board[ROWS][COLS], int rows, int columns, int players, int connect, int winCount) {
    if (emptyBoard(board,rows,columns) == 1){
        return 1;
    }
    winCount = playerAmount(board,rows,columns,players);
    if (winCount == -1){
        return 0
    } else if ()
    //win check
    //too many win check
    //for loop for all columns
    //player top calls recursion
    // recursion: checkValidBoard(board,rows,columns,players,(player-1),connect,wins)
    // Check if there are more than `connect` consecutive moves by any player
    if (countConnect >= connect) {
        return 0;
    }
    // Check if the stop condition count matches the maximum number of elements on the board
    if (stopCondCount == MAX_ELEMENTS) {
        // The board is valid
        return 1;
    } else {
        // Recursive call to isValidBoard, shrinking the board by one row or one column
        return isValidBoard(board, rows - 1, columns, players, connect) +
               isValidBoard(board, rows, columns - 1, players, connect);
    }
}

int topMoveCheck(char board[ROWS][COLS], int rows, int column, int player){
    for (int i = 0; i < rows; i++){
        if (board[i][column] == player){
            return 1;
        } else if ((board[i][column] != ' ') && (board[i][column] != player)){
            return 0;
        }
    }
    return 0;
}

/**
 * @brief Encodes the game board.
 *
 * This function encodes the game board into a string representation using Base64 encoding.
 *
 * @param board The game board.
 * @param rows The number of rows in the game board.
 * @param columns The number of columns in the game board.
 * @param code The encoded string representing the game board.
 */
void encode(const char board[ROWS][COLS], int rows, int columns, char *code) {
    // Counter for consecutive characters.
    int countChar = 0;
    // Index to track the position in the encoded code.
    int index = 0;
    // Encode the board
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < (columns - 1); j++) {
            char symbol = board[i][j];
            if (board[i][j] == board[i][j + 1]) {
                // Increment count for consecutive characters
                countChar++;
                // Check if the consecutive characters reach the maximum limit or the end of the row
                if (countChar == columns - 1 || j == (columns - 2)) {
                    // Encode the count and add it to the code
                    code[index++] = Base64(countChar);
                    // Add a space separator
                    code[index++] = ' ';
                    // Add a slash separator for rows
                    code[index++] = '/';
                    // Reset the count
                    countChar = 0;
                }
            } else {
                // Encode the count and the symbol if it is an uppercase letter
                code[index++] = Base64(countChar);
                if (symbol >= 'A' && symbol <= 'Z') {
                    code[index++] = symbol;
                }
                // If the previous index for code is equal to symbol reset count and iterate next.
                if (code[index - 1] == symbol) {
                    countChar = 0;
                    continue;
                } else {
                    // Add a space separator after encoding the character
                    code[index++] = ' ';
                }
                // reset countchar to 0.
                countChar = 0;
            }
        }
    }
    // put '\0' at the end of the array.
    code[index] = '\0';
}

/**
 * @brief Converts a count value to Base64 character.
 *
 * This function converts a count value to the corresponding Base64 character.
 *
 * @param countToChar The count value to be converted.
 * @return The Base64 character.
 */
char Base64(char countToChar) {
    // Constant offset to convert count to Base64 character. 66 because row no.1 is actually row 0.
    const int countTo64 = 66;
    // Add the offset to the count
    countToChar += countTo64;
    // Return the Base64 character
    return countToChar;
}

/**
 * @brief Decodes the encoded game board.
 *
 * This function decodes the encoded game board string and updates the game board accordingly.
 *
 * @param code The encoded string representing the game board.
 * @param board The game board to be updated.
 * @return when '\0' is reached, the last element of code[].
 */
void decode(const char *code, char board[ROWS][COLS]) {
    int i = 0, j = 0, index = 0, cpyRows = 0, count = 0;
    // constant max board size according to '/' = 64 in ascii.
    const int MAX_BOARD_SIZE = 4096;
    char symbol, nextSymbol;
    // a for loop to count the number of rows in the board.
    for (int t = 0; t < MAX_BOARD_SIZE; t++) {
        // '\0' reached the end of the array, break.
        if (code[index] == '\0') {
            break;
        } else {
            // '/' down a line, add a row to the count.
            if (code[index++] == '/') {
                cpyRows++;
            }
        }
    }
    // Resetting index to 0.
    index = 0;
    // A while loop while we didn't go through every row.
    while (i < cpyRows) {
        // Receiving a letter from code at the beginning.
        symbol = code[index++];
        // If we go down a line i++ and return to first column j = 0.
        if (symbol == '/') {
            i++;
            j = 0;
            // Continue to the next iteration.
            continue;
        }
        // Get the next symbol from code.
        nextSymbol = code[index++];
        // Symbols come in pairs of two, count for amount of insertions into board.
        count = symbol - 'A';
        // A for loop to insert the symbol to the correlating spaces in the matrix.
        for (count = count; count > 0; count--) {
            board[i][j++] = nextSymbol;
        }
    }
}

/**
 * @brief Converts the number of spaces to decimal.
 *
 * This function converts the number of spaces to decimal representation.
 *
 * @param numSpaces The number of spaces to be converted.
 * @return The decimal representation of the number of spaces.
 */
int decimalConvert(int numSpaces) {
    // Constant offset to convert spaces to decimal
    const int spacesToDecimal = 65;
    // Subtract the offset from the number of spaces
    numSpaces -= spacesToDecimal;
    // Return the decimal representation
    return numSpaces;
}