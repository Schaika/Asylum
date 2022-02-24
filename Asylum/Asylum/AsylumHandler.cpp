#include "AsylumHandler.h"
#include "InitialValues.h"
#include "randomGen.h"
#include <Strsafe.h>
AsylumHandler::AsylumHandler()
{

}

AsylumHandler::~AsylumHandler()
{
}

void AsylumHandler::nextDay()
{

	//новые работяги
	int newFollowers = randomGen::getNumberBetween(InitialValues.a1, InitialValues.b1);
	std::vector<UndeadBaseclass*> newFollowersList;

	for (int i = 0; i < newFollowers; i++) {
		auto obj = new UndeadBaseclass();
		obj->setName(generateName(obj->getSex()));
		newFollowersList.push_back(obj);
	}

	//чекаем че там у хохлов в палате
	std::vector<UndeadBaseclass*> candidateList;
	{
		auto pacient = pacientList.begin();
		while (pacient != pacientList.end()) {
			auto obj = *pacient;
			obj->addScore(double(randomGen::getNumberBetween(InitialValues.a4 * 10, InitialValues.b4 * 10)) / 10);

			if (obj->getScore() > InitialValues.a3) {
				//выписываем нах
				curedList.push_back(obj);
				pacient = pacientList.erase(pacient);
			}
			else {
				if (obj->getScore() > InitialValues.a5) {
					candidateList.push_back(obj);
				}
				pacient++;
			}
		}
	}
	{
		if (pacientList.size() + newFollowersList.size() > InitialValues.N1) {
			auto newPacient = newFollowersList.begin();
			while (newPacient != newFollowersList.end()) {
				auto obj = *newPacient;
				if (obj->getScore() > 41) {
					newPacient = newFollowersList.erase(newPacient);
					refusedList.push_back(obj);
				}
				else if(candidateList.size() > 0){
					auto candidate = *candidateList.begin();
					{
						auto pacient = std::find(pacientList.begin(), pacientList.end(), candidate);
						if (pacient == pacientList.end()) throw;
						pacientList.erase(pacient);
					}
					{
						auto pacient = std::find(candidateList.begin(), candidateList.end(), candidate);
						if (pacient == candidateList.end()) throw;
						candidateList.erase(pacient);
					}
					forcedOutList.push_back(candidate);

					pacientList.push_back(*newPacient);
					newPacient = newFollowersList.erase(newPacient);
				}
				else{
					//выгоняем больных на мороз, места нет. сорян
					auto i = newFollowersList.begin();
					while (i != newFollowersList.end()) {
						refusedList.push_back(*i);
						i = newFollowersList.erase(i);
					}
					break;
				}
			}
		}
		else {
			auto i = newFollowersList.begin();
			while (i != newFollowersList.end()) {
				pacientList.push_back(*i);
				i = newFollowersList.erase(i);
			}
		}
	}
	averageCapacity = (averageCapacity * (days-1) + pacientList.size())/days;
	days++;
	for (int i = 0; i < pacientList.size(); i++) pacientList.at(i)->daysSpent++;
}

void AsylumHandler::start()
{
	for (int i = 0; i < InitialValues.N2; i++) {
		auto obj = new UndeadBaseclass();
		obj->setName(generateName(obj->getSex()));
		pacientList.push_back(obj);
	}
	days++;
	averageCapacity = pacientList.size();
}

const std::vector<UndeadBaseclass*> AsylumHandler::getList()
{
	return pacientList;
}

void AsylumHandler::showStats()
{
	wchar_t buffer[512];

	double avgCureTime = 0.0f;
		if (curedList.size()) {
			for (int i = 0; i < curedList.size(); i++) avgCureTime += curedList.at(i)->daysSpent;
			avgCureTime = avgCureTime / curedList.size();
		}
		StringCbPrintfW(buffer, 512, L"Статистика за %d дней:\nВылечено больных: %d - среднее время лечения %.2f дней\nЗагрузка палаты: %d человек (в среднем %.2f)\nЧисло больных, которым отказано в лечении: %d\nЧисло больных, которых выписали досрочно: %d", days, curedList.size(), avgCureTime, pacientList.size(),averageCapacity, refusedList.size(),forcedOutList.size());
	MessageBoxW(NULL, buffer, L"Статистика", NULL);
}
std::wstring AsylumHandler::generateName(bool sex)
{
	std::wstring name;
		if (sex) {
			int nameNumber = randomGen::getNumberBetween(0, maleNames.size() - 1);
			int lastNameNumber = randomGen::getNumberBetween(0, lastNames.size() - 1);
			name = maleNames.at(nameNumber) + std::wstring(L" ") + lastNames.at(lastNameNumber);
			if (nameNumber == 0 && lastNameNumber == 0) {
				//ShellExecuteW(NULL, L"open", L"https://youtu.be/jy_TECJp5C8", NULL, NULL, SW_SHOWNORMAL);
				//MessageBoxW(NULL, L"СЛАВА УКРАИНЕ!", L"СЛАВА УКРАИНЕ!", NULL);
			}

		}
		else {
			int nameNumber = randomGen::getNumberBetween(0, femaleNames.size() - 1);
			int lastNameNumber = randomGen::getNumberBetween(0, lastNames.size() - 1);
			name = femaleNames.at(nameNumber) + std::wstring(L" ") + lastNames.at(lastNameNumber);
		}
		return name;
}
