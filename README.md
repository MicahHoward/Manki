# Manki
Manki is an open source program to retain and improve math skills. It utilizes a custom implementation of the FSRS algorithm to predict when a user is going to forget a skill, then it generates a problem for the user to solve, thus helping them remember the skill.

# How the program works
The majority of Manki's GUI code is in _MainFrame.cpp_. Code for generating problems for different skills are kept in the skills folder with a unique .cpp and .h file for each skill. Manki uses a SQL database to store a user's progression for a particular skill, as well as the addition of any user-defined timed skills. All the code accessing the database is kept in the db.cpp file.
