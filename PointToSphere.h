#pragma once

#include <filesystem>
#include <span>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

struct Point3D
{
    float x;
    float y;
    float z;
};

struct Point2D
{
    float x;
    float y;
};

struct PointSphere
{
    float ph; // phi 360
    float th; // theta 180
};

/// @brief Represents a point-to-sphere conversion and visibility calculation tool.
class PointToSphere {
public:
    /// @brief Default constructor (does nothing).
    PointToSphere() = default;

    /// @brief Destructor (does nothing by default).
    ~PointToSphere() = default;

    /// @brief Loads point data from a file.
    /// @param path The path to the file containing point data.
    /// @return True if the data was loaded successfully, false otherwise.
    bool loadFromFile(const std::filesystem::path& path);

    /// @brief Loads point data from a list of 3D points.
    /// @param points A reference to a span of 3D points.
    /// @return True if the data was loaded successfully, false otherwise.
    bool loadFromList(const std::span<Point3D>& points);

    /// @brief Sets the viewing angles for visibility calculations.
    /// @param angle1 The first viewing angle (in degrees).
    /// @param angle2 The second viewing angle (in degrees).
    void setAngle(float angle1);

    /// @brief Calculates and returns a list of visible 2D points based on the loaded data and viewing angles.
    /// @return A vector containing the visible points as 2D points.
    std::vector<Point2D> getVisiblePoints();

    /// @brief Returns the sphere's radius.
    /// @return The radius of the sphere.
    int getRadius() const { return radius_; }

private:
    /// @brief Converts a span of 3D points to their corresponding sphere coordinates.
    /// @param points A reference to a span of 3D points.
    /// @return A vector containing the converted points as PointSphere objects.
    std::vector<PointSphere> decardToSphere(const std::span<Point3D>& points);

    /// @brief Calculates the radius of a sphere based on a span of 3D points.
    /// @param points A reference to a span of 3D points.
    /// @return The calculated radius of the sphere.
    float calculateRadius(const std::span<Point3D>& points);

private:
    /// @brief The radius of the sphere.
    float radius_ = 0;

    /// @brief The list of points stored in sphere coordinates.
    std::vector<PointSphere> points_;

    /// @brief The first viewing angle for visibility calculations (in degrees).
    float angle1_ = 0;
};
