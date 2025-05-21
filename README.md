# indexing-patients
Implementing a patient record management system using an AVL tree to store and retrieve patient data 

This C program implements a patient record management system using an AVL tree to store and retrieve patient data efficiently. Patients are organized by BMI values, enabling quick lookups and balanced insertions. For patients with the same BMI, a linked list is maintained at each AVL tree node.

Features
Load patient data from a file.

Display all patients in-order (sorted by BMI).

Search for a patient with a specific BMI.

Identify and display the youngest patient.

Menu-driven interface for user interaction.

File Structure
main.c — Main application logic and menu loop.

avltree.h — Header file declaring data structures and AVL-related operations (assumed to be provided).

Input file — A semicolon-separated list of patient records.
