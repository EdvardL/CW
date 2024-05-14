#include <PointToSphere.h>

#include <imgui.h>

#include <string>
#include <map>
#include <iostream>
#include <filesystem>

namespace ImGui
{
    static bool VisualizationOfPoints_error_file = false;
    void VisualizationOfPoints(
        const char* label, 
        PointToSphere& points,
        float &angle,
        int &radius,
        int &pointsCount,
        char* pathBuffer,
        int pathBufferSize,
        ImVec2 size = {0, 0}, 
        ImVec4 bgColor = {0,0,0,0},
        ImVec4 circleColor = {0.5, 0.5, 0.5, 1},
        ImVec4 pointsColor = {1,1,1,1},
        bool showBorder = false
    )
    {
        ImGui::InputText("Path to csv", pathBuffer, pathBufferSize);
        if (ImGui::Button("Open file"))
        {
            VisualizationOfPoints_error_file = !points.loadFromFile(pathBuffer);
        }
        if (VisualizationOfPoints_error_file) ImGui::Text("Choose another file!");
        ImGui::Separator();
        ImGui::InputInt("Points count", &pointsCount);
        ImGui::Separator();
        ImGui::SliderFloat("Angle", &angle, 0, 360);
        auto drawList = ImGui::GetWindowDrawList();
        if (pointsCount > points.getVisiblePoints().size()) ImGui::Text("Visualisation error");

        ImGui::BeginChild(label, size, showBorder);

        drawList->AddRectFilled(ImGui::GetItemRectMin(), {ImGui::GetItemRectMin().x + size.x, ImGui::GetItemRectMin().y + size.y}, ImGui::GetColorU32(bgColor));
        drawList->AddCircleFilled({ImGui::GetItemRectMin().x + size.x/2, ImGui::GetItemRectMin().y + size.y/2}, points.getRadius(), ImGui::GetColorU32(circleColor));

        points.setAngle(angle);

        for (int i = 0; i < ((pointsCount != -1 && pointsCount < points.getVisiblePoints().size()) ? pointsCount : points.getVisiblePoints().size()); i += 1)
        {
            drawList->AddCircleFilled({ImGui::GetItemRectMin().x + points.getRadius() + points.getVisiblePoints()[i].x, ImGui::GetItemRectMin().y + points.getRadius() + points.getVisiblePoints()[i].y}, 3, ImGui::GetColorU32(pointsColor));
        }
        ImGui::Text("%s", std::string("r - " + std::to_string(points.getRadius())).c_str());

        ImGui::EndChild();
    }
}