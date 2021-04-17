#include <unistd.h>
#include <cstdio>

typedef struct StatusInfo
{
    int currentStatus = -1;
    int parentStatusIndex = -1;
}StatusInfo;

int initStatus;
int destStatus;
int destStatusInfoIndex;

// 值为 9! 
StatusInfo statusQueue[362880];
int startIndex;
int endIndex;
// 位图数组来标识某个状态值是否已经被遍历过
int statusFlagBit[876543210 / 32 + 1];
char chessBoard[3][3];

/**
 * 将描述某个状态的 int 值插入位图数组中 
 */
void insertNum(int num) {
	int index = num / 32;
	int mod = num % 32;
	statusFlagBit[index] |= (1 << (31 - mod));
}

/**
 * 检测 int 值对应的状态是否已经遍历过
 */
bool isExists(int num) {
	int index = num / 32;
	int mod = num % 32;
	return ((statusFlagBit[index] >> (31 - mod)) & 1);
}

bool addStatusInfo(StatusInfo statusInfo) {
    if (isExists(statusInfo.currentStatus)) {
        return false;
    }
    statusQueue[endIndex++] = statusInfo;
    insertNum(statusInfo.currentStatus);
    return true;
}

int getIntByChessBoard() {
    int res = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            res = res * 10 + chessBoard[i][j] - '0';
        }
    }
    return res;
}

void initChessBoard() {
    initStatus = 0;
    printf("输入初始状态：\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            chessBoard[i][j] = getchar();
            if (chessBoard[i][j] < '0' || chessBoard[i][j] > '8') {
                fprintf(stderr, "状态输入错误！\n");
                _exit(-1);
            }
            initStatus = initStatus * 10 + chessBoard[i][j] - '0';
        }
    }
    StatusInfo initStatusInfo;
    initStatusInfo.currentStatus = initStatus;
    addStatusInfo(initStatusInfo);
}

void swapChessElement(int row1, int col1, int row2, int col2) {
    char temp = chessBoard[row1][col1];
    chessBoard[row1][col1] = chessBoard[row2][col2];
    chessBoard[row2][col2] = temp;
}

void move(StatusInfo currentStatus, int index) {
    int curStatusInt = currentStatus.currentStatus;
    int spaceRow = -1;
    int spaceCol = -1;
    for (int i = 2; i >= 0; i--) {
        for (int j = 2; j >= 0; j--) {
            chessBoard[i][j] = curStatusInt % 10 + '0';
            curStatusInt /= 10;
            if (chessBoard[i][j] == '0') {
                spaceRow = i;
                spaceCol = j;
            }
        }
    }
    if (spaceRow == -1 || spaceCol == -1) {
        fprintf(stderr, "状态出现错误！\n");
        _exit(1);
    }
    int tempRow = spaceRow;
    int tempCol = spaceCol;
    StatusInfo nextStatusInfo;

    // 尝试上下左右移动
    // 上移
    if (spaceRow > 0) {
        tempRow = spaceRow - 1;
        tempCol = spaceCol;
        swapChessElement(tempRow, tempCol, spaceRow, spaceCol);
        nextStatusInfo.currentStatus = getIntByChessBoard();
        nextStatusInfo.parentStatusIndex = index;
        addStatusInfo(nextStatusInfo);
        // 回溯，用于下一次使用
        swapChessElement(tempRow, tempCol, spaceRow, spaceCol);
    }
    // 下移
    if (spaceRow < 2) {
        tempRow = spaceRow + 1;
        tempCol = spaceCol;
        swapChessElement(tempRow, tempCol, spaceRow, spaceCol);
        nextStatusInfo.currentStatus = getIntByChessBoard();
        nextStatusInfo.parentStatusIndex = index;
        addStatusInfo(nextStatusInfo);
        // 回溯，用于下一次使用
        swapChessElement(tempRow, tempCol, spaceRow, spaceCol);
    }
    // 左移
    if (spaceCol > 0) {
        tempRow = spaceRow;
        tempCol = spaceCol - 1;
        swapChessElement(tempRow, tempCol, spaceRow, spaceCol);
        nextStatusInfo.currentStatus = getIntByChessBoard();
        nextStatusInfo.parentStatusIndex = index;
        addStatusInfo(nextStatusInfo);
        // 回溯，用于下一次使用
        swapChessElement(tempRow, tempCol, spaceRow, spaceCol);
    }
    // 右移
    if (spaceCol < 2) {
        tempRow = spaceRow;
        tempCol = spaceCol + 1;
        swapChessElement(tempRow, tempCol, spaceRow, spaceCol);
        nextStatusInfo.currentStatus = getIntByChessBoard();
        nextStatusInfo.parentStatusIndex = index;
        addStatusInfo(nextStatusInfo);
        // 回溯，用于下一次使用
        swapChessElement(tempRow, tempCol, spaceRow, spaceCol);
    }
}

bool bfs() {
    StatusInfo currentStatusInfo;
    int tempIndex;
    do {
        tempIndex = startIndex;
        currentStatusInfo = statusQueue[startIndex++];
        if (currentStatusInfo.currentStatus == destStatus) {
            destStatusInfoIndex = tempIndex;
            return true;
        }
        move(currentStatusInfo, tempIndex);
    } while(startIndex < endIndex);
    return false;
}

int doPrint(int statusInfoIndex) {
    int stepCount = 0;
    if (statusInfoIndex == -1) {
        return stepCount;
    }
    StatusInfo statusInfo = statusQueue[statusInfoIndex];
    if (statusInfo.parentStatusIndex != -1) {
        stepCount += doPrint(statusInfo.parentStatusIndex);
        printf("|\n|");
    } else {
        stepCount--;
    }
    int tempStatusInt = statusInfo.currentStatus;
    for (int i = 2; i >= 0; i--) {
        for (int j = 2; j >= 0; j--) {
            chessBoard[i][j] = tempStatusInt % 10 + '0';
            tempStatusInt /= 10;
        }
    }
    printf("\n%c%c%c\n%c%c%c\n%c%c%c\n", chessBoard[0][0], chessBoard[0][1], chessBoard[0][2],
        chessBoard[1][0], chessBoard[1][1], chessBoard[1][2], chessBoard[2][0], chessBoard[2][1], chessBoard[2][2]);
    return stepCount + 1;
}

int main() {
    initChessBoard();
    printf("输入目标状态：\n");
    scanf("%d", &destStatus);

    if (bfs()) {
        int stepCount = doPrint(destStatusInfoIndex);
        printf("\n使用步数：%d\n", stepCount);
    } else {
        printf("从初始状态无法到达目标状态！\n");
    }

    return 0;
}