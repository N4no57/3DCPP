#include "../include/objParser.hpp"
#include <fstream>
#include <string>
#include <iostream>

namespace rast {
    std::vector<std::string> splitByLine(std::fstream& file) {
        std::vector<std::string> result;
        std::string buff;

        for (char c; c = file.get(); ) {
            if (c == '\n') {
                result.push_back(buff);
                buff.clear();
            } else {
                buff.append(1, c);
            }
            if (c == EOF) {
                break;
            }
        }

        return result;
    }

    auto split(std::string str, std::string delimiter) {
        std::vector<std::string> result;
        std::string buff;

        for (int i = 0; i < str.size(); i++) {
            if (str[i] == delimiter[0] || i == str.size() - 1) {
                if (buff == "") {
                    continue;
                }

                result.push_back(buff);
                buff.clear();
            } else {
                buff.append(1, str[i]);
            }
        }

        return result;
    }

    auto to_float(std::vector<std::string> input) {
        std::vector<float> result;

        for (int i = 0; i < input.size(); i++) {
            result.push_back(atof(input[i].c_str()));
        }

        return result;
    }

    auto to_int(std::vector<std::string> input) {
        std::vector<int> result;

        for (int i = 0; i < input.size(); i++) {
            result.push_back(atoi(input[i].c_str()));
        }

        return result;
    }

    std::vector<float3> loadObjectFile(std::string filename) {
        std::vector<float3> allPoints;
        std::vector<float3> trianglePoints;

        std::fstream f;
        f.open(filename, std::ios::in);
        std::filebuf* buf = f.rdbuf();

        auto lines = splitByLine(f);

        for (int i = 0; i < lines.size(); i++) {
            if (lines[i].starts_with("v ")) {
                lines[i].replace(lines[i].find("v "), 2, "");
                std::vector<float> axes = to_float(split(lines[i], " "));
                allPoints.push_back(float3(axes[0], axes[1], axes[2]));
            } else if (lines[i].starts_with("f ")) {
                lines[i].replace(lines[i].find("f "), 2, "");
                std::vector<std::string> faceIndexGroups = split(lines[i], " ");

                for (int j = 0; j < faceIndexGroups.size(); j++) {
                    std::vector<int> indexGroup = to_int(split(faceIndexGroups[j], "/"));
                    int pointIndex = indexGroup[0] - 1;
                    if (j >= 3) trianglePoints.push_back(trianglePoints[trianglePoints.size() - (3 * j - 6)]);
                    if (j >= 3) trianglePoints.push_back(trianglePoints[trianglePoints.size() - 2]);
                    trianglePoints.push_back(allPoints[pointIndex]);
                }
            }
        }
        return trianglePoints;
    }
}
