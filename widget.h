#include <PointToSphere.h>

#include <imgui.h>

#include <string>
#include <map>
#include <iostream>

namespace ImGui
{
    void VisualizationOfPoints(
        const char* label, 
        PointToSphere& points, 
        ImVec2 size = {0, 0}, 
        ImVec4 bgColor = {0,0,0,0},
        ImVec4 circleColor = {0.5, 0.5, 0.5, 1},
        ImVec4 pointsColor = {1,1,1,1},
        bool showBorder = false,
        float angle1 = 0
    )
    {
        auto drawList = ImGui::GetWindowDrawList();

        ImGui::BeginChild(label, size, showBorder);

        drawList->AddRectFilled(ImGui::GetItemRectMin(), {ImGui::GetItemRectMin().x + size.x, ImGui::GetItemRectMin().y + size.y}, ImGui::GetColorU32(bgColor));
        drawList->AddCircleFilled({ImGui::GetItemRectMin().x + size.x/2, ImGui::GetItemRectMin().y + size.y/2}, points.getRadius(), ImGui::GetColorU32(circleColor));

        points.setAngle(angle1);

        int i = 0;
        for (auto point : points.getVisiblePoints())
        {
            drawList->AddCircleFilled({ImGui::GetItemRectMin().x + points.getRadius() + point.x, ImGui::GetItemRectMin().y + points.getRadius() + point.y}, 3, ImGui::GetColorU32(pointsColor));
            i+=1;
        }
        ImGui::Text("%s", std::string("r - " + std::to_string(points.getRadius())).c_str());

        ImGui::EndChild();
    }
}