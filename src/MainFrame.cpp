#include "MainFrame.h"
#include "skills/addition.h"
#include "skills/subtraction.h"
#include "skills/multiplication.h"
#include <wx/wx.h>
#include <wx/simplebook.h>
#include "backend.h"

static wxSimplebook* main_book;
wxStaticText* skill_name;
std::string solution;
wxStaticBitmap* image;

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {
        wxBoxSizer* main_sizer = new wxBoxSizer(wxVERTICAL); 
        main_book = new wxSimplebook(this, wxID_ANY);
        main_sizer->Add(main_book, 1, wxEXPAND);

        wxPanel* main_panel = new wxPanel(main_book);
        wxButton* addition_button = new wxButton(main_panel, wxID_ANY, "Addition", wxPoint(150,50), wxSize(100,35));
        wxButton* subtraction_button = new wxButton(main_panel, wxID_ANY, "Subtraction", wxPoint(150,150), wxSize(100,35));
        wxButton* multiplication_button = new wxButton(main_panel, wxID_ANY, "Multiplication", wxPoint(150,250), wxSize(100,35));

        addition_button->Bind(wxEVT_BUTTON, &MainFrame::OnAdditionButtonClicked, this);
        subtraction_button->Bind(wxEVT_BUTTON, &MainFrame::OnSubtractionButtonClicked, this);
        multiplication_button->Bind(wxEVT_BUTTON, &MainFrame::OnMultiplicationButtonClicked, this);

       CreateStatusBar();

        main_book->AddPage(main_panel, "Welcome");

        wxPanel* skill_panel = new wxPanel(main_book, wxID_ANY);
        skill_name = new wxStaticText(skill_panel, wxID_ANY, "Addition", wxPoint(350, 150), wxSize(100, 35));
        wxButton* back_button = new wxButton(skill_panel, wxID_ANY, "Back", wxPoint(150, 150), wxSize(100,35));
        wxTextCtrl* textEntry = new wxTextCtrl(skill_panel, wxID_ANY, "", wxPoint(150,350), wxSize(100,35), wxTE_PROCESS_ENTER);
        back_button->Bind(wxEVT_BUTTON, &MainFrame::OnBackButtonClicked, this);
        textEntry->Bind(wxEVT_TEXT, &MainFrame::OnTextChanged, this);
        textEntry->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnTextEntered, this);
        
        //image stuff
        image = new wxStaticBitmap( skill_panel, wxID_ANY, wxBitmap("problem.png", wxBITMAP_TYPE_PNG), wxPoint(50,100), wxSize(100, 500));
        wxBoxSizer* boxSizer = new wxBoxSizer(wxHORIZONTAL);
        boxSizer->Add(image, 0, wxCENTER | wxALL, 10);
        skill_panel->SetSizer(boxSizer);

 

        main_book->AddPage(skill_panel, "Welcome");
}


void MainFrame::OnAdditionButtonClicked(wxCommandEvent& evt) {
        wxLogStatus("Button clicked");
        std::string* problem_and_solution = generate_addition_problem();
        std::cout << "Made it to image gen \n";
        generate_latex_image(problem_and_solution[0]);
        std::cout << "Made it past image gen";
        image->SetBitmap(wxBitmap("problem.png", wxBITMAP_TYPE_PNG));
        skill_name->SetLabel(problem_and_solution[0]);
        solution = problem_and_solution[1];
        main_book->SetSelection(1);

}
void MainFrame::OnSubtractionButtonClicked(wxCommandEvent& evt) {
        wxLogStatus("Button clicked");
        std::string* problem_and_solution = generate_subtraction_problem();
        generate_latex_image("a-b=c");
        image->SetBitmap(wxBitmap("problem.png", wxBITMAP_TYPE_PNG));
        skill_name->SetLabel(problem_and_solution[0]);
        solution = problem_and_solution[1];
        main_book->SetSelection(1);
}
void MainFrame::OnMultiplicationButtonClicked(wxCommandEvent& evt) {
        wxLogStatus("Button clicked");
        std::string* problem_and_solution = generate_multiplication_problem();
        generate_latex_image(problem_and_solution[0]);
        image->SetBitmap(wxBitmap("problem.png", wxBITMAP_TYPE_PNG));
        skill_name->SetLabel(problem_and_solution[0]);
        solution = problem_and_solution[1];
        main_book->SetSelection(1);
}
void MainFrame::OnTextChanged(wxCommandEvent& evt) {
        wxString str = wxString::Format("Text: %s", evt.GetString());
        wxLogStatus(str);
}

void MainFrame::OnTextEntered(wxCommandEvent& evt) {
        if(evt.GetString() == solution){
                wxMessageBox(wxT("Correct"));
        } else{
                wxMessageBox(wxT("Incorrect, solution was " + solution));
        }
}

void MainFrame::OnBackButtonClicked(wxCommandEvent& evt) {
        main_book->SetSelection(0);
}
