#pragma once

#include <iostream>
#include "../DataStructures/HashTable.h"
#include "../DataStructures/Stack.h"

using namespace std;

class Survey
{
public:
    char surveyId[20];          
    char title[200];            
    char description[500];      
    char questions[10][200];    
    int numQuestions;

    // Targeting
    char targetSector[50];      
    int minAge;
    int maxAge;

    // Status
    bool isActive;
    int totalResponses;

    Survey()
    {
        surveyId[0] = '\0';
        title[0] = '\0';
        description[0] = '\0';
        numQuestions = 0;
        targetSector[0] = '\0';
        minAge = 0;
        maxAge = 100;
        isActive = true;
        totalResponses = 0;
    }

    Survey(const char* id, const char* surveyTitle, const char* desc)
    {
        int i = 0;
        while (id[i] != '\0' && i < 19) {
            surveyId[i] = id[i];
            i++;
        }
        surveyId[i] = '\0';

        i = 0;
        while (surveyTitle[i] != '\0' && i < 199) {
            title[i] = surveyTitle[i];
            i++;
        }
        title[i] = '\0';

        i = 0;
        while (desc[i] != '\0' && i < 499) {
            description[i] = desc[i];
            i++;
        }
        description[i] = '\0';

        numQuestions = 0;
        targetSector[0] = '\0';
        minAge = 0;
        maxAge = 100;
        isActive = true;
        totalResponses = 0;
    }

    void addQuestion(const char* question)
    {
        if (numQuestions < 10) {
            int i = 0;
            while (question[i] != '\0' && i < 199) {
                questions[numQuestions][i] = question[i];
                i++;
            }
            questions[numQuestions][i] = '\0';
            numQuestions++;
        }
    }

    void display()
    {
        cout << endl;
        cout << "   SURVEY: " << title << endl;
        cout << endl;
        cout << "Survey ID:    " << surveyId << endl;
        cout << "Description:  " << description << endl;
        cout << "Target:       " << targetSector << " (Age " << minAge
            << "-" << maxAge << ")" << endl;
        cout << "Status:       " << (isActive ? "Active" : "Closed") << endl;
        cout << "Responses:    " << totalResponses << endl;
        cout << "\nQuestions:" << endl;
        for (int i = 0; i < numQuestions; i++) {
            cout << (i + 1) << ". " << questions[i] << endl;
        }
        cout << endl;
    }
};

class SurveyResponse
{
public:
    char cnic[20];              
    char surveyId[20];          
    int answers[10];            
    char feedback[500];         
    char timestamp[50];        

    SurveyResponse()
    {
        cnic[0] = '\0';
        surveyId[0] = '\0';
        for (int i = 0; i < 10; i++) {
            answers[i] = 0;
        }
        feedback[0] = '\0';
        timestamp[0] = '\0';
    }

    SurveyResponse(const char* citizenCNIC, const char* survId)
    {
        int i = 0;
        while (citizenCNIC[i] != '\0' && i < 19) {
            cnic[i] = citizenCNIC[i];
            i++;
        }
        cnic[i] = '\0';

        i = 0;
        while (survId[i] != '\0' && i < 19) {
            surveyId[i] = survId[i];
            i++;
        }
        surveyId[i] = '\0';

        for (int j = 0; j < 10; j++) {
            answers[j] = 0;
        }
        feedback[0] = '\0';
        timestamp[0] = '\0';
    }
};

class SurveyManager
{
private:
    HashTable* activeSurveys;       
    HashTable* surveyResponses;     
    Stack* surveyHistory;          

public:
    SurveyManager()
    {
        activeSurveys = new HashTable(100);
        surveyResponses = new HashTable(100);
        surveyHistory = new Stack();
    }

    void createSurvey(const char* surveyId, const char* title, const char* description)
    {
        Survey* survey = new Survey(surveyId, title, description);
        activeSurveys->insert(surveyId, (void*)survey);

        cout << "\n*** Survey Created ***" << endl;
        cout << "Survey ID: " << surveyId << endl;
        cout << "Title: " << title << endl;
    }

    void addQuestionToSurvey(const char* surveyId, const char* question)
    {
        Survey* survey = (Survey*)activeSurveys->search(surveyId);

        if (survey == NULL) {
            cout << "Survey " << surveyId << " not found!" << endl;
            return;
        }

        survey->addQuestion(question);
        cout << "Question added to survey " << surveyId << endl;
    }

    void setSurveyTarget(const char* surveyId, const char* sector, int minAge, int maxAge)
    {
        Survey* survey = (Survey*)activeSurveys->search(surveyId);

        if (survey == NULL) {
            cout << "Survey " << surveyId << " not found!" << endl;
            return;
        }

        int i = 0;
        while (sector[i] != '\0' && i < 49) {
            survey->targetSector[i] = sector[i];
            i++;
        }
        survey->targetSector[i] = '\0';

        survey->minAge = minAge;
        survey->maxAge = maxAge;

        cout << "Survey target set: " << sector << ", Age " << minAge
            << "-" << maxAge << endl;
    }

    void submitResponse(const char* cnic, const char* surveyId,
        int* answers, int numAnswers, const char* feedback)
    {
        Survey* survey = (Survey*)activeSurveys->search(surveyId);

        if (survey == NULL) {
            cout << "Survey " << surveyId << " not found!" << endl;
            return;
        }

        if (!survey->isActive) {
            cout << "Survey is closed!" << endl;
            return;
        }

        SurveyResponse* response = new SurveyResponse(cnic, surveyId);

        for (int i = 0; i < numAnswers && i < 10; i++) {
            response->answers[i] = answers[i];
        }

        if (feedback != NULL) {
            int i = 0;
            while (feedback[i] != '\0' && i < 499) {
                response->feedback[i] = feedback[i];
                i++;
            }
            response->feedback[i] = '\0';
        }

        // Store response 
        survey->totalResponses++;

        cout << "\n*** Survey Response Submitted ***" << endl;
        cout << "Thank you for your feedback!" << endl;
        cout << "Survey: " << survey->title << endl;
    }

    void displaySurvey(const char* surveyId)
    {
        Survey* survey = (Survey*)activeSurveys->search(surveyId);

        if (survey == NULL) {
            cout << "Survey " << surveyId << " not found!" << endl;
            return;
        }

        survey->display();
    }

    void closeSurvey(const char* surveyId)
    {
        Survey* survey = (Survey*)activeSurveys->search(surveyId);

        if (survey == NULL) {
            cout << "Survey " << surveyId << " not found!" << endl;
            return;
        }

        survey->isActive = false;
        surveyHistory->push((void*)survey);

        cout << "Survey '" << survey->title << "' closed" << endl;
        cout << "Total responses: " << survey->totalResponses << endl;
    }

    void displayActiveSurveys()
    {
        cout << endl;
        cout << "       ACTIVE SURVEYS.........." << endl;
        cout << endl;
        activeSurveys->display();
        cout << endl;
    }

    ~SurveyManager()
    {
        delete activeSurveys;
        delete surveyResponses;
        delete surveyHistory;
    }
};