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

/// @brief Представляет инструмент для преобразования точек в сферу и расчета видимости.
class PointToSphere {
public:
    /// @brief Конструктор по умолчанию (не выполняет ничего).
    PointToSphere() = default;

    /// @brief Деструктор (по умолчанию не делает ничего).
    ~PointToSphere() = default;

    /// @brief Загружает данные точек из файла.
    /// @param path Путь к файлу с данными точек.
    /// @return True, если данные были успешно загружены, иначе false.
    bool loadFromFile(const std::filesystem::path& path);

    /// @brief Загружает данные точек из списка 3D точек.
    /// @param points Ссылка на диапазон 3D точек.
    /// @return True, если данные были успешно загружены, иначе false.
    bool loadFromList(const std::span<Point3D>& points);

    /// @brief Устанавливает углы обзора для расчета видимости.
    /// @param angle1 Первый угол обзора (в градусах).
    void setAngle(float angle1);

    /// @brief Рассчитывает и возвращает список видимых 2D точек на основе загруженных данных и углов обзора.
    /// @return Вектор, содержащий видимые точки как 2D точки.
    std::vector<Point2D> getVisiblePoints();

    /// @brief Возвращает радиус сферы.
    /// @return Радиус сферы.
    int getRadius() const { return radius_; }

private:
    /// @brief Преобразует диапазон 3D точек в их соответствующие сферические координаты.
    /// @param points Ссылка на диапазон 3D точек.
    /// @return Вектор, содержащий преобразованные точки как объекты PointSphere.
    std::vector<PointSphere> decardToSphere(const std::span<Point3D>& points);

    /// @brief Рассчитывает радиус сферы на основе диапазона 3D точек.
    /// @param points Ссылка на диапазон 3D точек.
    /// @return Рассчитанный радиус сферы.
    float calculateRadius(const std::span<Point3D>& points);

private:
    /// @brief Радиус сферы.
    float radius_ = 0;

    /// @brief Список точек, сохраненных в сферических координатах.
    std::vector<PointSphere> points_;

    /// @brief Первый угол обзора для расчетов видимости (в градусах).
    float angle1_ = 0;
};
