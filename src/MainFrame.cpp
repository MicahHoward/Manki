#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/simplebook.h>
#include <wx/intl.h>
#include <wx/collpane.h>
#include "backend.h"
#include "db.h"
#include "fsrs.h"
#include <chrono>
#include <thread>
#include <map>

static wxSimplebook* main_book;
wxBoxSizer* main_sizer = new wxBoxSizer(wxVERTICAL);
std::string solution;
wxStaticBitmap* image;
wxBoxSizer* box_sizer = new wxBoxSizer(wxVERTICAL);
wxBoxSizer* browser_box_sizer = new wxBoxSizer(wxVERTICAL);
int current_skill_id = 0;
wxTextCtrl* textEntry; 
wxCollapsiblePane* due_coll_pane; 
wxCollapsiblePane* learnt_coll_pane; 
wxCollapsiblePane* unlearnt_coll_pane; 
wxCollapsiblePane* not_retaining_coll_pane; 
wxWindow* due_win;
wxWindow* learnt_win;
wxWindow* unlearnt_win;
wxWindow* not_retaining_win;
wxSizer* due_sizer;
wxSizer* learnt_sizer;
wxSizer* unlearnt_sizer;
wxSizer* not_retaining_sizer;
int due_coll_pane_height;
int learnt_coll_pane_height;
int unlearnt_coll_pane_height;
int not_retaining_coll_pane_height;

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {
        initialize_database();
        insert_default_values();
        update_retrievability();

        // Creates
        main_book = new wxSimplebook(this, wxID_ANY);

        //
        auto main_panel = new wxPanel(main_book);
        due_coll_pane = new wxCollapsiblePane(main_panel, 200, "Due Skills:", wxDefaultPosition, wxSize(400, 20));
        learnt_coll_pane = new wxCollapsiblePane(main_panel, 201, "Learnt Skills:", wxDefaultPosition, wxSize(400, 20));
        unlearnt_coll_pane = new wxCollapsiblePane(main_panel, 202, "Unlearnt Skills:", wxDefaultPosition, wxSize(400, 20));
        wxStaticBitmap* logo = new wxStaticBitmap(main_panel, wxID_ANY, wxBitmap(wxImage(wxBitmap("logo.png", wxBITMAP_TYPE_PNG).ConvertToImage()).Scale(200,200)), wxPoint(150,50), wxSize(200, 200));
        wxButton* browser_button = new wxButton(main_panel, wxID_ANY, "Skill Browser", wxPoint(150,50), wxSize(100,35));
        browser_button->Bind(wxEVT_BUTTON, &MainFrame::OnBrowserButtonClicked, this);
        int number_of_skills = get_number_of_skills();

        // For whatever reason, wxWidgets doesn't like adding controls to the coll_pane itself
        // So we use GetPane() to add controls to it.
        due_win = due_coll_pane->GetPane();
        learnt_win = learnt_coll_pane->GetPane();
        unlearnt_win = unlearnt_coll_pane->GetPane();
        due_sizer = new wxGridSizer(0, 2, 0, 0);
        learnt_sizer = new wxGridSizer(0, 2, 0, 0);
        unlearnt_sizer = new wxGridSizer(0, 2, 0, 0);
        due_win->SetSizer(due_sizer);
        learnt_win->SetSizer(learnt_sizer);
        unlearnt_win->SetSizer(unlearnt_sizer);
        due_sizer->SetSizeHints(due_win);
        learnt_sizer->SetSizeHints(learnt_win);
        unlearnt_sizer->SetSizeHints(unlearnt_win);
        main_sizer->Add(logo, wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
        main_sizer->Add(browser_button, 0, wxALIGN_CENTER, 5);
        main_sizer->Add(due_coll_pane, 0, wxALIGN_CENTER, 5);
        main_sizer->Add(learnt_coll_pane, 0, wxALIGN_CENTER, 5);
        main_sizer->Add(unlearnt_coll_pane, 0, wxALIGN_CENTER, 5);

        main_panel->SetSizer(main_sizer);
        
        main_book->Bind(wxEVT_COLLAPSIBLEPANE_CHANGED, &MainFrame::OnCollapsiblePaneClicked, this);

        // Sets up browser panel 
        wxPanel* browser_panel = new wxPanel(main_book);
        wxButton* browser_back_button = new wxButton(browser_panel, wxID_ANY, "Main Menu", wxPoint(150,50), wxSize(100,35));
        browser_back_button->Bind(wxEVT_BUTTON, &MainFrame::OnBackButtonClicked, this);
        wxStaticBitmap* browser_panel_logo = new wxStaticBitmap(browser_panel, wxID_ANY, wxBitmap(wxImage(wxBitmap("logo.png", wxBITMAP_TYPE_PNG).ConvertToImage()).Scale(200,200)), wxPoint(150,50), wxSize(200, 200));
        
        browser_panel->SetSizer(browser_box_sizer);
        not_retaining_coll_pane = new wxCollapsiblePane(browser_panel, 203, "New Skills", wxDefaultPosition, wxSize(400, 20));
        not_retaining_win = not_retaining_coll_pane->GetPane();
        not_retaining_sizer = new wxGridSizer(0, 2, 0, 0);
        not_retaining_win->SetSizer(not_retaining_sizer);
        not_retaining_sizer->SetSizeHints(not_retaining_win);
        browser_box_sizer->Add(browser_panel_logo, wxSizerFlags().CenterHorizontal().Border(wxRIGHT | wxLEFT, 40));
        browser_box_sizer->Add(browser_back_button, 0, wxALIGN_CENTER, 5);
        browser_box_sizer->Add(not_retaining_coll_pane, 0, wxALIGN_CENTER, 5);

        // Creates buttons for each skill
        std::string* skill_names = get_skill_names();


        std::map<int, int> skill_status;
        int current_skill_status;

        for(int i = 0; i < number_of_skills; i++){
               current_skill_status = get_skill_status(i+1); 
               skill_status[i] = current_skill_status;

        }

        MainFrame::UpdateMainPanel(); 

        main_book->AddPage(main_panel, "Welcome");

        wxPanel* skill_panel = new wxPanel(main_book, wxID_ANY);
        wxButton* back_button = new wxButton(skill_panel, wxID_ANY, "Back", wxPoint(150,50), wxSize(100,35));
        textEntry = new wxTextCtrl(skill_panel, wxID_ANY, "", wxPoint(150,50), wxSize(400,35), wxTE_PROCESS_ENTER);
        back_button->Bind(wxEVT_BUTTON, &MainFrame::OnBackButtonClicked, this);
        textEntry->Bind(wxEVT_TEXT, &MainFrame::OnTextChanged, this);
        textEntry->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnTextEntered, this);
        
        //image stuff
        image = new wxStaticBitmap(skill_panel, wxID_ANY, wxBitmap("problem.png", wxBITMAP_TYPE_PNG), wxPoint(150,50), wxSize(400, 100), wxCENTER);
        box_sizer->Add(back_button, 0, wxCENTER | wxALL, 10);
        box_sizer->Add(image, 0, wxCENTER | wxALL, 10);
        box_sizer->Add(textEntry, 0, wxCENTER | wxALL, 10);
        skill_panel->SetSizer(box_sizer);
        main_book->AddPage(skill_panel, "Practice");
        main_book->AddPage(browser_panel, "New Skills");
}

void MainFrame::UpdateMainPanel(){

        int number_of_skills = get_number_of_skills();
        due_win->DestroyChildren();
        learnt_win->DestroyChildren();
        unlearnt_win->DestroyChildren();
        not_retaining_win->DestroyChildren();

        due_coll_pane_height = 20;
        learnt_coll_pane_height = 20;
        unlearnt_coll_pane_height = 20;
        not_retaining_coll_pane_height = 20;
        
        // Creates buttons for each skill
        std::string* skill_names = get_skill_names();


        std::map<int, int> skill_status;
        int current_skill_status;

        for(int i = 0; i < number_of_skills; i++){
               current_skill_status = get_skill_status(i+1); 
               skill_status[i] = current_skill_status;

        }
        bool not_retaining = false;
        for(int i = 0; i < number_of_skills; i++){
                // wx_IDs may not be one or zero, so we use 2i for the skill button and 2i+1 for the stats button
                wxSizerFlags flags = wxSizerFlags().Expand();
                switch(skill_status[i])
                {
                        case 0:
                                due_coll_pane_height += 35;
                                due_sizer->Add(new wxButton(due_win, 2*(i+1), skill_names[i]), flags); 
                                due_sizer->Add(new wxButton(due_win, 2*(i+1) + 1, "Stats"), flags);
                                due_coll_pane->Fit();
                                //due_coll_pane->SetMinSize(wxSize(400,due_coll_pane_height));
                                due_sizer->Layout();
                                break;
                        case 1:
                                learnt_coll_pane_height += 35;
                                learnt_sizer->Add(new wxButton(learnt_win, 2*(i+1), skill_names[i]), flags);
                                learnt_sizer->Add(new wxButton(learnt_win, 2*(i+1) + 1, "Stats"), flags);
                                learnt_coll_pane->Fit();
                                learnt_sizer->Layout();
                                break;
                        case 2:
                                if(get_skill_retaining(i+1) == "TRUE"){
                                        unlearnt_coll_pane_height += 35;
                                        unlearnt_sizer->Add(new wxButton(unlearnt_win, 2*(i+1), skill_names[i]), flags);
                                        unlearnt_sizer->Add(new wxButton(unlearnt_win, 2*(i+1) + 1, "Stats"), flags);
                                        unlearnt_coll_pane->Fit();
                                        unlearnt_sizer->Layout();

                                        break;
                                } else{

                                        not_retaining_coll_pane_height += 35;
                                        not_retaining_sizer->Add(new wxButton(not_retaining_win, 2*(i+1), skill_names[i]), flags);
                                        not_retaining_sizer->Add(new wxButton(not_retaining_win, 2*(i+1) + 1, "Add Skill"), flags);
                                        Connect(2*(i+1), wxEVT_BUTTON, wxCommandEventHandler(MainFrame::OnSkillButtonClicked));
                                        Connect(2*(i+1) + 1, wxEVT_BUTTON, wxCommandEventHandler(MainFrame::OnAddSkillButtonClicked));
                                        not_retaining = true;
                                        learnt_coll_pane->Fit();
                                        learnt_sizer->Layout();

                                        break;
                                }
                        default:
                                throw std::invalid_argument("Invalid skill status");
                }
                if(not_retaining == false){
                        Connect(2*(i+1), wxEVT_BUTTON, wxCommandEventHandler(MainFrame::OnSkillButtonClicked));
                        Connect(2*(i+1) + 1, wxEVT_BUTTON, wxCommandEventHandler(MainFrame::OnStatsButtonClicked));
                }
                not_retaining = false;
        }

        // Adds text to empty windows
        if(due_win->GetChildren().size() == 0){
                due_coll_pane_height+= 35;
                due_sizer->Add(new wxStaticText(due_win, wxID_ANY, "No skills due"), 0, wxALIGN_CENTER);
                due_coll_pane->Fit();
                due_sizer->Layout();
        }
        if(learnt_win->GetChildren().size() == 0){
                learnt_coll_pane_height+= 35;
                learnt_sizer->Add(new wxStaticText(learnt_win, wxID_ANY, "No skills learnt and not due"), 0, wxALIGN_CENTER);
                learnt_coll_pane->Fit();
                learnt_sizer->Layout();
        }
        if(unlearnt_win->GetChildren().size() == 0){
                unlearnt_coll_pane_height+= 35;
                unlearnt_sizer->Add(new wxStaticText(unlearnt_win, wxID_ANY, "No skills unlearnt"), 0, wxALIGN_CENTER);
                unlearnt_coll_pane->Fit();
                unlearnt_sizer->Layout();
        }
        if(not_retaining_win->GetChildren().size() == 0){
                not_retaining_coll_pane_height += 35;
                not_retaining_sizer->Add(new wxStaticText(not_retaining_win, wxID_ANY, "No skills to add"), 0, wxALIGN_CENTER);
                not_retaining_coll_pane->Fit();
                not_retaining_sizer->Layout();
        }
        not_retaining_sizer->Layout();
        browser_box_sizer->Layout();
        main_sizer->Layout();
}

void MainFrame::OnCollapsiblePaneClicked(wxCollapsiblePaneEvent& evt) {
                
                main_sizer->Layout();
                int adjusted_pane_id = evt.GetId();
                int adjusted_pane_height;
                wxCollapsiblePane* adjusted_pane; 

                switch(adjusted_pane_id){
                        case 200:
                                adjusted_pane = due_coll_pane;
                                adjusted_pane_height = due_coll_pane_height;
                                break;
                        case 201:
                                adjusted_pane = learnt_coll_pane;
                                adjusted_pane_height = learnt_coll_pane_height;
                                break;
                        case 202:
                                adjusted_pane = unlearnt_coll_pane;
                                adjusted_pane_height = unlearnt_coll_pane_height;
                                break;
                        case 203:
                                adjusted_pane = not_retaining_coll_pane;
                                adjusted_pane_height = not_retaining_coll_pane_height;
                }


                if(adjusted_pane->IsCollapsed() == true){
                        adjusted_pane->SetMinSize(wxSize(400, 20));
                } else{
                        adjusted_pane->SetMinSize(wxSize(400, adjusted_pane_height));
                }
                due_sizer->Layout();
                learnt_sizer->Layout();
                unlearnt_sizer->Layout();
                not_retaining_sizer->Layout();
                main_sizer->Layout();
                browser_box_sizer->Layout();

}

void MainFrame::OnSkillButtonClicked(wxCommandEvent& evt) {
        // skillIDs start at 1 and button ids start at 2, so we subtract 1
        int skillID = (evt.GetId()/2);
        std::string* problem_and_solution = generate_problem(skillID);

        // TODO: REPLACE THIS GARBAGE BY SWITCHING TO MicroLaTeX OR SOME OTHER LIBRARY
        int mypid = fork();

        if(0 == mypid){
                char* args[]={"./latex_generator", problem_and_solution[0].data(), "problem.png", NULL};
                execvp(args[0], args);

        }
        // waits for
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        image->SetBitmap(wxBitmap("problem.png", wxBITMAP_TYPE_PNG));
        solution = problem_and_solution[1];
        std::string stupid_string = ".";
        if(solution.contains(stupid_string)){
                for(int i = 0; i < solution.size(); i++){
                        if(solution.at(i) == stupid_string){
                                solution = solution.substr(0, i+3);
                                break;
                        }
                }

        }
        current_skill_id = skillID;
        main_book->SetSelection(1);

}

void MainFrame::GenerateNewProblem(int skillID) {
        // skillIDs start at 1 and button ids start at 2, so we subtract 1
        std::string* problem_and_solution = generate_problem(skillID);

        // TODO: REPLACE THIS GARBAGE BY SWITCHING TO MicroLaTeX OR SOME OTHER LIBRARY
        int mypid = fork();

        if(0 == mypid){
                char* args[]={"./latex_generator", problem_and_solution[0].data(), "problem.png", NULL};
                execvp(args[0], args);

        }
        // waits for
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        image->SetBitmap(wxBitmap("problem.png", wxBITMAP_TYPE_PNG));
        solution = problem_and_solution[1];
        std::string stupid_string = ".";
        if(solution.contains(stupid_string)){
                for(int i = 0; i < solution.size(); i++){
                        if(solution.at(i) == stupid_string){
                                solution = solution.substr(0, i+3);
                                break;
                        }
                }

        }
        current_skill_id = skillID;
        main_book->SetSelection(1);

}



void MainFrame::OnBrowserButtonClicked(wxCommandEvent& evt) {
        main_book->SetSelection(2);
        textEntry->Clear();
}

void MainFrame::OnStatsButtonClicked(wxCommandEvent& evt) {
        // skillIDs start at 1 and button ids start at 2, so we subtract 1
        int skillID = ((evt.GetId()-1)/2);
        std::string stats = get_skill_info(skillID);
        std::string skill_name = get_skill_name(skillID);

        wxMessageBox(stats, skill_name + " Stats");
}

void MainFrame::OnAddSkillButtonClicked(wxCommandEvent& evt) {
        // skillIDs start at 1 and button ids start at 2, so we subtract 1
        int skillID = ((evt.GetId()-1)/2);
        update_skill_value(skillID, "RETAINING", "TRUE");

        wxMessageBox("Skill Added!");
        wxWindow* skill_ctrl = wxWindow::FindWindowById(evt.GetId()-1, this);
        wxWindow* add_ctrl = wxWindow::FindWindowById(evt.GetId(), this);
        skill_ctrl->Destroy();
        add_ctrl->Destroy();
        browser_box_sizer->Layout(); 
        MainFrame::UpdateMainPanel();
        main_sizer->Layout();

}



void MainFrame::OnTextChanged(wxCommandEvent& evt) {
        wxString str = wxString::Format("Text: %s", evt.GetString());
}

void MainFrame::OnTextEntered(wxCommandEvent& evt) {
        if(return_spaceless_string(std::string(evt.GetString())) == return_spaceless_string(solution)){
                wxMessageBox(wxT("The solution was \"" + solution + "\"."), "Correct!");
                update_fsrs_on_answer(current_skill_id, 3);
                textEntry->Clear();
                MainFrame::UpdateMainPanel();
                main_book->SetSelection(0);
        } else{
                wxMessageBox(wxT("The solution was \"" + solution + "\"."), "Incorrect!");
                update_fsrs_on_answer(current_skill_id, 1);
                textEntry->Clear();
                MainFrame::GenerateNewProblem(current_skill_id);
        }
}

void MainFrame::OnBackButtonClicked(wxCommandEvent& evt) {
        main_book->SetSelection(0);
        textEntry->Clear();
        main_sizer->Layout();
}
