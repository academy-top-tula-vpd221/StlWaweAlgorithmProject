#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

enum class FieldType
{
    Space = -1,
    Start = 0,
    Finish = -2,
    Wall = -3
};

struct Point
{
    int row;
    int col;
    friend bool operator ==(Point p1, Point p2)
    {
        return p1.row == p2.row && p1.col == p2.col;
    }
};

char wall{ (char)178 };

vector<Point> diff{ {-1, 0}, {0, 1}, {1, 0}, {0, -1} };


typedef vector<vector<int>> matrix;

//matrix MapRead(string fileName, Point& start, Point& finish)
//{
//    // чтение текстового файла с картой и формирование карты
//}

void MapPrint(matrix Map)
{
    cout << "\n";

    for (int i = 0; i < Map.size(); i++)
    {
        for (int j = 0; j < Map[0].size(); j++)
        {
            switch ((FieldType)Map[i][j])
            {
            case FieldType::Space: cout << setw(2) << " "; break;
            case FieldType::Start: cout << setw(2) << "S"; break;
            case FieldType::Finish: cout << setw(2) << "F"; break;
            case FieldType::Wall: cout << wall << wall; break;
            default:
                cout << setw(2) << Map[i][j];
            }
        }
        cout << "\n";
    }
}

void MapPrintFinal(matrix Map, vector<Point> way)
{
    cout << "\n";

    for (int i = 0; i < Map.size(); i++)
    {
        for (int j = 0; j < Map[0].size(); j++)
        {
            switch ((FieldType)Map[i][j])
            {
            case FieldType::Space: cout << setw(2) << " "; break;
            case FieldType::Start: cout << setw(2) << "S"; break;
            case FieldType::Finish: cout << setw(2) << "F"; break;
            case FieldType::Wall: cout << wall << wall; break;
            default:
                Point pointCurr{ i, j };
                bool isWay{ false };
                for (int k = 0; k < way.size(); k++)
                    if (way[k] == pointCurr)
                        isWay = true;
                
                if (isWay)
                    cout << setw(2) << Map[i][j];
                else
                    cout << setw(2) << " ";
            }
        }
        cout << "\n";
    }
}

int main()
{
    matrix Map{ {-3, -3, -3, -3, -3, -3, -3, -3, -3},
                {-3, 0,  -1, -3, -1, -1, -1, -1, -3},
                {-3, -1, -1, -3, -1, -3, -1, -1, -3},
                {-3, -1, -1, -1, -1, -3, -1, -1, -3},
                {-3, -3, -3, -1, -1, -3, -1, -3, -3},
                {-3, -1, -1, -1, -1, -3, -1, -2, -3},
                {-3, -3, -3, -3, -3, -3, -3, -3, -3} };
    
    Point start{ 1, 1 };
    Point finish{ 5, 7 };

    MapPrint(Map);

    bool frontCurr{ false };
    int frontNumber{ 1 };
    vector<Point>* fronts = new vector<Point>[2];
    vector<Point> way;

    fronts[frontCurr].push_back(start);

    bool isBreak{ false };
    bool isFinish{ false };

    while (1)
    {
        fronts[!frontCurr].clear();
        for (int i = 0; i < fronts[frontCurr].size(); i++)
        {
            int row = fronts[frontCurr][i].row;
            int col = fronts[frontCurr][i].col;
            for (int d = 0; d < diff.size(); d++)
            {
                int drow = row + diff[d].row;
                int dcol = col + diff[d].col;
                if (Map[drow][dcol] == (int)FieldType::Space)
                {
                    Map[drow][dcol] = frontNumber;
                    fronts[!frontCurr].push_back(Point{ drow, dcol });
                }
                    
                if (Map[drow][dcol] == (int)FieldType::Finish)
                {
                    Map[drow][dcol] = frontNumber;
                    isBreak = true;
                    isFinish = true;
                }
            }
            if (isBreak) break;
        }
        if (isBreak) break;
        if (fronts[!frontCurr].size() == 0) break;
        frontCurr = !frontCurr;
        frontNumber++;
        MapPrint(Map);
    }
    

    if (!isFinish)
    {
        cout << "Opps, map not exit!\n";
        return 0;
    }
    way.push_back(finish);
    int step = Map[finish.row][finish.col];
    while (1)
    {
        for (int d = 0; d < diff.size(); d++)
        {
            int row = way[way.size() - 1].row;
            int col = way[way.size() - 1].col;
            int drow = row + diff[d].row;
            int dcol = col + diff[d].col;
            if (Map[drow][dcol] == step - 1)
            {
                way.push_back(Point{ drow, dcol });
                step--;
                break;
            }
        }
        if (step == 0)
        {
            way.push_back(start);
            break;
        }
    }

    MapPrintFinal(Map, way);


    return 0;
}
