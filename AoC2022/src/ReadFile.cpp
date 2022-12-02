#include "ReadFile.h"

void ReadFile01(const char* filename, std::vector<int>& data)
{
    std::ifstream myfile(filename);

    std::string line;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            if (line.size() > 0)
            {
                data.push_back(std::stoi(line));            
            }
            else
            {
                data.push_back(0);
            }
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";
}

void ReadFile(const char* filename, std::vector<int>& data)
{
    std::ifstream myfile(filename);

    std::string line;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            while (line.size() > 0)
            {
                std::size_t pos = line.find(",");
                if (pos != std::string::npos)
                {
                    data.push_back(std::stoi(line.substr(0, pos)));
                    line = line.substr(pos + 1, line.size());
                }
                else
                {
                    data.push_back(std::stoi(line));
                    getline(myfile, line);
                    break;
                }
            }
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";
}

void ReadFile(const char* filename, std::vector<float>& data)
{
    std::ifstream myfile(filename);

    std::string line;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            data.push_back(std::stof(line.c_str()));
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";
}

void ReadFile(const char* filename, std::vector<std::pair<std::string, int>>& data)
{
    std::ifstream myfile(filename);

    std::string line;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {

            std::size_t pos = line.find(" ");

            std::string command = line.substr(0,pos);
            int value = std::stoi(line.substr(pos, line.size()));

            std::pair<std::string, int> commandPair;
            commandPair.first = command;
            commandPair.second = value;

            data.push_back(commandPair);
            
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";

}

void ReadFile(const char* filename, std::vector<std::pair<std::string, std::string>>& data)
{
    std::ifstream myfile(filename);

    std::string line;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {

            std::size_t pos = line.find(" ");

            std::string command = line.substr(0, pos);
            std::string value = line.substr(pos+1, line.size());

            std::pair<std::string, std::string> commandPair;
            commandPair.first = command;
            commandPair.second = value;

            data.push_back(commandPair);

        }
        myfile.close();
    }
    else std::cout << "Unable to open file";

}

void ReadFile(const char* filename, std::vector<std::string>& data)
{
    std::ifstream myfile(filename);

    std::string line;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            data.push_back(line);
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";

}

void ReadFile(const char* filename, std::vector<int>& data, std::vector<std::vector<std::vector<std::pair<int, bool>>>>& boards)
{
    std::ifstream myfile(filename);

    int N = 5; // Board size NxN

    std::string line;
    if (myfile.is_open())
    {
        // lee la primera linea de datos
        getline(myfile, line);
        std::string ss = line;
        while (ss.size() > 0)
        {
            std::size_t pos = ss.find(",");
            if (pos != std::string::npos)
            {
                data.push_back(std::stoi(ss.substr(0, pos)));
                ss = ss.substr(pos + 1, ss.size());
            }
            else
            {
                data.push_back(std::stoi(ss));
                getline(myfile, line);
                break;
            }
        }
        
        // lee los datos de boards
        std::vector<std::pair<int, bool>> row;
        std::vector<std::vector<std::pair<int, bool>>> board;

        while (getline(myfile, line))
        {
            if (line != "")
            {
                for (int j = 0; j < N; j++)
                {
                    std::pair<int, bool> cell;
                    cell.first = std::stoi(line.substr(j * 3, 3));
                    cell.second = false;
                    row.push_back(cell);
                }

                board.push_back(row);
                row.clear();

                if (board.size() == N)
                {
                    boards.push_back(board);
                    board.clear();
                }


            }
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";

}

void ReadFile(const char* filename, std::vector<int>& x0, std::vector<int>& y0, std::vector<int>& x1, std::vector<int>& y1)
{
    std::ifstream myfile(filename);
    std::string line;

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            std::size_t pos = line.find(",");
            if (pos != std::string::npos)
            {
                x0.push_back(std::stoi(line.substr(0, pos)));
                line = line.substr(pos + 1, line.size());
            }

            pos = line.find("->");
            if (pos != std::string::npos)
            {
                y0.push_back(std::stoi(line.substr(0, pos+1)));
                line = line.substr(pos + 2, line.size());
            }

            pos = line.find(",");
            if (pos != std::string::npos)
            {
                x1.push_back(std::stoi(line.substr(0, pos)));
                y1.push_back(std::stoi(line.substr(pos+1, line.size())));
            }
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";

}

void ReadFile(const char* filename, std::vector<std::vector<std::string>>& patern, std::vector<std::vector<std::string>>& output)
{
    std::ifstream myfile(filename);

    std::string line;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            std::vector<std::string> paternrow;
            std::vector<std::string> outputrow;
            std::size_t pos = line.find("|");
            if (pos != std::string::npos)
            {
                std::string linepatern = line.substr(0, pos-1);
                std::string lineoutput = line.substr(pos + 2, line.size());

                std::string str = linepatern;
                for (int i = 0; i < 10; i++)
                {
                    std::size_t p = str.find(" ");
                    paternrow.push_back(str.substr(0, p));
                    str = str.substr(p + 1, str.size());

                }

                str = lineoutput;
                for (int i = 0; i < 4; i++)
                {
                    std::size_t p = str.find(" ");
                    outputrow.push_back(str.substr(0, p));
                    str = str.substr(p + 1, str.size());
                }

                patern.push_back(paternrow);
                output.push_back(outputrow);
            }
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";

}

void ReadFile(const char* filename, std::vector<std::vector<int>>& data)
{
    std::ifstream myfile(filename);

    std::string line;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            std::vector<int> row;
            for (int j = 0; j < line.size(); j++)
                row.push_back(line[j]-'0');

            data.push_back(row);
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";

}

void ReadFile12(const char* filename, std::vector<std::string>& data)
{
    std::ifstream myfile(filename);

    std::string line;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            data.push_back(line);
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";

}

void ReadFile13(const char* filename, std::vector<std::pair<int, int>>& data, int& x, int& y)
{
    std::ifstream myfile(filename);

    std::string line;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            if (line != "")
            {
                std::size_t pos = line.find(",");
                if (pos != std::string::npos)
                {
                    std::pair<int, int> xy;
                    xy.first = std::stoi(line.substr(0, pos));
                    xy.second = std::stoi(line.substr(pos+1, line.size()));
                    data.push_back(xy);
                }
                else
                {
                    pos = line.find("x=");
                    if (pos != std::string::npos)
                        x = std::stoi(line.substr(pos+2, line.size()));
                    pos = line.find("y=");
                    if (pos != std::string::npos)
                        y = std::stoi(line.substr(pos + 2, line.size()));
                }
            }
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";
}

void ReadFile14(const char* filename, std::string& polymerTemplate, std::map<std::string, std::string>& input)
{
    std::ifstream myfile(filename);

    std::string line;
    if (myfile.is_open())
    {
        getline(myfile, polymerTemplate);
        getline(myfile, line);

        while (getline(myfile, line))
        {
            std::size_t pos = line.find("->");
            if (pos != std::string::npos)
            {
                std::string chain = line.substr(0, pos - 1);
                std::string letter = line.substr(pos + 3, line.size());
                input[chain] = letter;
            }
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";
}

void ReadFile16(const char* filename, std::string& data)
{
    std::ifstream myfile(filename);

    std::string line;
    if (myfile.is_open())
    {
        getline(myfile, data);
        myfile.close();
    }
    else std::cout << "Unable to open file";
}

//void ReadFile19(const char* filename, std::vector<std::vector<Vec>>& scanners)
//{
//    std::ifstream myfile(filename);
//
//    std::string line;
//    if (myfile.is_open())
//    {
//        std::vector<Vec> scanner;
//        while (getline(myfile, line))
//        {
//            if (line.substr(0, 3) != "---")
//            {
//                if (line.size() >1)
//                {
//                    Vec beacon;
//                    std::string ss = line;
//                    std::size_t pos;
//                    pos = ss.find(",");
//                    beacon.x = std::stoi(ss.substr(0, pos));
//                    ss = ss.substr(pos+1, ss.size());
//
//                    pos = ss.find(",");
//                    beacon.y = std::stoi(ss.substr(0, pos));
//                    beacon.z = std::stoi(ss.substr(pos+1, ss.size()));
//                    scanner.push_back(beacon);
//                }
//                else
//                {
//                    scanners.push_back(scanner);
//                    scanner.resize(0);
//                }
//            }
//        }
//        scanners.push_back(scanner);
//        myfile.close();
//    }
//    else std::cout << "Unable to open file";
//}

void ReadFile20(const char* filename, std::vector<bool>& iea, std::vector<std::vector<bool>>& image)
{
    std::ifstream myfile(filename);

    std::string line;
    if (myfile.is_open())
    {
        getline(myfile, line);

        for (int i = 0; i < line.size(); i++)
            if (line[i] == '.')
                iea.push_back(false);
            else
                iea.push_back(true);

        getline(myfile, line);

        while (getline(myfile, line))
        {
            std::vector<bool> row;
            for (int i = 0; i < line.size(); i++)
                if (line[i] == '.')
                    row.push_back(false);
                else
                    row.push_back(true);

            image.push_back(row);
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";

}

void ReadFile22(const char* filename, std::vector<bool>& states, std::vector<std::pair<int, int>>& X, std::vector<std::pair<int, int>>& Y, std::vector<std::pair<int, int>>& Z)
{
    std::ifstream myfile(filename);

    std::string line;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            // State
            int pos0 = line.find(" ");
            std::string state_str = line.substr(0, pos0);
            if (state_str == "on")
                states.push_back(true);
            else
                states.push_back(false);

            line = line.substr(pos0 + 1);
            std::string x_str = line.substr(0, line.find(","));
            line = line.substr(line.find(",")+1);
            std::string y_str = line.substr(0, line.find(","));
            std::string z_str = line.substr(line.find(",") + 1);

            std::pair<int, int> x, y, z;
            x.first = std::stoi(x_str.substr(x_str.find("=") + 1, x_str.find(".")));
            x.second = std::stoi(x_str.substr(x_str.find(".")+2));

            y.first = std::stoi(y_str.substr(y_str.find("=") + 1, y_str.find(".")));
            y.second = std::stoi(y_str.substr(y_str.find(".") + 2));

            z.first = std::stoi(z_str.substr(z_str.find("=") + 1, z_str.find(".")));
            z.second = std::stoi(z_str.substr(z_str.find(".") + 2));

            X.push_back(x);
            Y.push_back(y);
            Z.push_back(z);

            //data.push_back(line);
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";

}