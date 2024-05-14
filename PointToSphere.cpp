#include <PointToSphere.h>
#include <string>

bool PointToSphere::loadFromFile(const std::filesystem::path &path)
{
    std::vector<Point3D> newPoints;
    if ( path.is_relative() && path.filename().extension() == ".csv")
    {
        std::fstream inputfile(path.string());

        if (inputfile.is_open())
        {
            std::string line;
            while (std::getline(inputfile, line))
            {
                std::string number;
                std::vector<float> numbers;
                std::stringstream lieneString(line);
                while (std::getline(lieneString, number, ';'))
                {
                    std::cout<<number<<std::endl;
                    numbers.push_back(stof(number));
                }
                if (numbers.size() == 3)
                {
                    newPoints.push_back({numbers[0], numbers[1], numbers[2]});
                }
                else return false;
            }
            inputfile.close();
            points_ = decardToSphere(newPoints);
            radius_ = calculateRadius(newPoints);
            return true;
        }
        else return false;
    }
    else
    {
        std::cerr<<"File not exist or file not csv"<<std::endl;
        return false;
    }
}
bool PointToSphere::loadFromList(const std::span<Point3D> &points)
{
    points_ = decardToSphere(points);
    radius_ = calculateRadius(points);
    return true;
}
void PointToSphere::setAngle(float angle1)
{
    angle1_ = angle1;
}
std::vector<Point2D> PointToSphere::getVisiblePoints()
{
    std::vector<Point2D> output;
    for (auto point : points_) 
    {
        {
            Point2D newPoint;
            newPoint.x = radius_ * sin(point.th + (angle1_* M_PI / 180) ) * cos(point.ph);
            newPoint.y = radius_ * sin(point.th) * sin(point.ph);
            output.push_back(newPoint);
        }
    }
    return output;
}
std::vector<PointSphere> PointToSphere::decardToSphere(const std::span<Point3D> &points)
{
    std::vector<PointSphere> sphericalPoints;
    for (const auto& point : points) 
    {
        PointSphere sphericalPoint;
        sphericalPoint.th = acos(point.z / sqrt(point.x*point.x + point.y*point.y + point.z*point.z));
        sphericalPoint.ph = atan2(point.y, point.x);
        sphericalPoints.push_back(sphericalPoint);
    }
    return sphericalPoints;
}
float PointToSphere::calculateRadius(const std::span<Point3D> &points)
{
    if (!points.empty()) return std::sqrt(std::pow(points[0].x, 2) + std::pow(points[0].y, 2) + std::pow(points[0].z, 2));
    else return -1;
}