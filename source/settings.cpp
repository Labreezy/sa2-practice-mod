#include "settings.h"

static bool ppSkipToggle = 0;
static bool esgToggle = 0;

//void Settings::resetPP() {
//	// 
//}

void Settings::RenderTab() {
	if (ImGui::CollapsingHeader("Settings")) {
		ImGui::Checkbox("Emblem Skip Glitch", &esgFlag);
		ImGui::Checkbox("PP Skip Reset", &ppSkipToggle);
		ImGui::SetTooltip("If checked, reset the variable that pushes the kart forward for 120 frames on every load/restart. Only relevant for Route 101/280.");
		//ImGui::InputInt2("Times Restarted or Died", (int*)TimesRestartedOrDied);
		//ImGui::SameLine(); HelpMarker(
		//	"Adjusts the number of times the player has died or restarted."
		//	"This is relevant for Egg Golem, where the boss delays itself"
		//);
	}
}