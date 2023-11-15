

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "library.h"
#define MAXNAME 64

// Declare a structure to represent an employee
extern FILE *file; // variable: read data file
struct employee    // Data structure used to store employees into the DB
{
    char fname[MAXNAME];
    char lname[MAXNAME];
    int id;
    int salary;
};

// Global variables
struct employee db[1024]; // An array to store employee records in the database
int employee_counter = 0; // Keeps track of the number of employees in the DB



void Swap(struct employee *xp, struct employee *yp)
{
    struct employee temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// sort salary in decreasing order
void SelectionSortSalary(struct employee arr[], int n)
{
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++)
    {

        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j].salary > arr[min_idx].salary)
                min_idx = j;

        Swap(&arr[min_idx], &arr[i]);
    }
}



// if employee id is in the DB, remove employee and reduce size in DB
void RemoveEmployee(struct employee arr[], int n)
{
    int i;
    int choice;

    printf("\nName\t\t\t\tSALARY\t   ID\n");
    printf("----------------------------------------------\n");
    printf("%-15s\t%-15s\t%d\t%d\n", arr[n].fname, arr[n].lname, arr[n].salary, arr[n].id);
    printf("----------------------------------------------\n");
    printf("Delete this employee? Enter 1 for Yes, or 0 for No.\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        for (i = n; i < employee_counter; i++)
        {
            arr[i] = arr[i + 1];
        }
        employee_counter--;
    }
    else if (choice == 0)
    {
        printf("\nCancelling Action.\n");
    }
    else
    {
        printf("\nInvalid entry. Cancelling action\n");
    }
}

// Function to perform Selection Sort on Employee ID
void SelectionSort(struct employee arr[], int n)
{
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++)
    {

        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j].id < arr[min_idx].id)
                min_idx = j;

        Swap(&arr[min_idx], &arr[i]);
    }
}

// This function initiates a prompt to inquire whether the user intends to modify the employee data based on an entered employee ID. The user is provided with the option to select either a specific field or update all fields. If the user decides to change the employee ID, the function ensures that the database is re-sorted accordingly.
int UpdateEmployee(struct employee arr[], int x)
{
    int option;
    char fname[MAXNAME], lname[MAXNAME];
    int salaryNew, idNew;

    printf("\nName\t\t\t\tSALARY\t   ID\n");
    printf("----------------------------------------------\n");
    printf("%-15s\t%-15s\t%d\t%d\n", arr[x].fname, arr[x].lname, arr[x].salary, arr[x].id);
    printf("----------------------------------------------\n");

    printf("Would you like to edit the information of this employee? Enter 1 for Yes, or 0 for No.\n");
    printf("Enter your choice: ");
    scanf("%d", &option);

    if (option == 0)
    {
        printf("\nCancelling action\n");
        return 0;
    }

    printf("\nWhich information would you like to change?\n");
    printf("\t(1) First Name\n");
    printf("\t(2) Last Name\n");
    printf("\t(3) Salary\n");
    printf("\t(4) Employee ID\n");
    printf("\t(5) All of the Employee's Data\n");
    printf("Enter your choice: ");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        printf("\n Please enter the updated first name: ");
        scanf("%s", fname);
        break;
    case 2:
        printf("\n Please enter the updated last name: ");
        scanf("%s", lname);
        break;
    case 3:
        printf("\n Please enter the updated salary: ");
        scanf("%d", &salaryNew);
        break;
    case 4:
        printf("\n Please enter the updated employee ID: ");
        scanf("%d", &idNew);
        break;
    case 5:
        printf("\n Please enter the updated first name: ");
        scanf("%s", fname);
        printf("\n Please enter the updated last name: ");
        scanf("%s", lname);
        printf("\n Please enter the updated salary: ");
        scanf("%d", &salaryNew);
        printf("\n Please enter the updated employee ID: ");
        scanf("%d", &idNew);
        break;
    default:
        printf("\nInvalid entry. Cancelling action\n");
        return 0;
    }

    if (option != 0)
    {
        printf("\nName\t\t\t\tSALARY\t   ID\n");
        printf("----------------------------------------------\n");
        printf("%-15s\t%-15s\t%d\t%d\n", arr[x].fname, arr[x].lname, arr[x].salary, arr[x].id);
        printf("----------------------------------------------\n");

        printf("Is this information correct? Enter 1 for Yes, or 0 for No.\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        if (option == 1)
        {
            printf("\nUpdate Complete.\n");
            strcpy(arr[x].fname, fname);
            strcpy(arr[x].lname, lname);
            arr[x].salary = salaryNew;
            arr[x].id = idNew;

            if (option == 4 || option == 5)
            {
                SelectionSort(arr, employee_counter);
            }
        }
        else if (option == 0)
        {
            printf("\nUpdate Cancelled.\n");
        }
        else
        {
            printf("\nInvalid entry. Cancelling action\n");
        }
    }

    return 0;
}

/* This function performs a linear search to look up a user in the database based on their last name.
It returns all employees with the specified last name in the search. If the user is not found,
it displays a "User not found" message. */
int LookupByLastName(struct employee arr[], int n, char *lastName)
{
    int i, h, s;
    int userFound = -1;
    char searchLastName[MAXNAME], currentLastName[MAXNAME];

    s = strlen(lastName);
    for (i = 0; i < s; i++)
    {
        searchLastName[i] = tolower(lastName[i]);
    }

    printf("\nName\t\t\t\tSALARY\t   ID\n");
    printf("----------------------------------------------\n");
    for (i = 0; i < n; i++)
    {
        s = strlen(arr[i].lname);
        for (h = 0; h < s; h++)
        {
            currentLastName[h] = tolower(arr[i].lname[h]);
        }
        if (strcmp(searchLastName, currentLastName) == 0)
        {
            printf("%-15s\t%-15s\t%d\t%d\n", arr[i].fname, arr[i].lname, arr[i].salary, arr[i].id);
            userFound = 0;
        }
        memset(&currentLastName[0], 0, sizeof(currentLastName)); // clears the 'currentLastName' string for the next name
    }
    printf("----------------------------------------------\n");

    return userFound;
}

// Function to look up a user from the DB by Employee ID using binary search
int LookupID(struct employee arr[], int l, int r, int x)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;

        if (arr[mid].id == x)
            return mid;

        if (arr[mid].id > x)
            return LookupID(arr, l, mid - 1, x);

        return LookupID(arr, mid + 1, r, x);
    }

    return -1; // Element not found
}

// Function to print the database
void PrintDB(struct employee x[], int x_size)
{
    int i;

    printf("\nName\t\tSALARY\t   ID\n");
    printf("------------------\n");
    for (i = 0; i < x_size; i++)
    {
        printf("%-15s\t%-15s\t%d\t%d\n", x[i].fname, x[i].lname, x[i].salary, x[i].id);
    }
    printf("------------------\n");
    printf(" Number of Employees (%d)\n", x_size);
}

void PrintHighestSalary(struct employee arr[], int n)
{
    struct employee salaryDB[n];
    int i;
    int choice;
    
    for (i = 0; i < n; i++)
    {
        salaryDB[i] = arr[i];
    }

    SelectionSortSalary(salaryDB, n);
    printf("\nPlease enter how many employees you want to view with the highest salaries\n");
    printf("Enter your choice: ");

    scanf("%d", &choice); //Read user choice for DB menu
    if (choice > n)
    {
        choice = n;
    }
    PrintDB(salaryDB, choice);

}

// Function to add an employee to the DB
int AddEmployee(struct employee arr[])
{
    char newfname[MAXNAME];
    char newlname[MAXNAME];
    int newsalary;
    int confirm;

    printf("\nFirst name of the employee: ");
    scanf("%s", newfname);
    if (strlen(newfname) > 64)
    {
        printf("Invalid entry. Please try again.\n");
        return 0;
    }
    printf("First name of the employee: ");
    scanf("%s", newlname);
    if (strlen(newfname) > 64)
    {
        printf("Invalid entry. Please try again.\n");
        return 0;
    }
    printf("Enter employee's salary (30000 to 150000): ");
    scanf("%d", &newsalary);
    if (newsalary < 30000 || newsalary > 150000)
    {
        printf("Invalid entry. Please try again.\n");
        return 0;
    }
    printf("\nDo you want to add the following employee to the DB?\n");
    printf("\t%s %s, \tSalary: %d\n", newfname, newlname, newsalary);
    printf("\nEnter 1 for yes, 0 for no: ");
    scanf("%d", &confirm);

    if (confirm == 1)
    {
        strcpy(db[employee_counter].fname, newfname);
        strcpy(db[employee_counter].lname, newlname);
        db[employee_counter].salary = newsalary;
        db[employee_counter].id = db[employee_counter - 1].id + 1;
        employee_counter++;
        printf("New employee added!\n");
    }
    return 1;
}

// Function to look up a user from the DB by last name using linear search, return only one that is first in DB
int LookupLName(struct employee arr[], int m, char *name)
{
    int i, h, s;
    int check = -1;
    char testname1[MAXNAME], testname2[MAXNAME];

    s = strlen(name);
    for (i = 0; i < s; i++)
    {
        testname1[i] = tolower(name[i]);
    }

    for (i = 0; i < m; i++)
    {
        s = strlen(arr[i].lname);
        for (h = 0; h < s; h++)
        {
            testname2[h] = tolower(arr[i].lname[h]);
        }
        if (strcmp(testname1, testname2) == 0)
        {
            return i;
        }
        memset(&testname2[0], 0, sizeof(testname2)); // clears the 'testname2' string for the next name
    }
    return -1;
}

// Function to create the database by loading data from a file
void CreateDB(char *datafile)
{
    if (open_file(datafile) == 0)
    {
        char buffer[135];
        int ret;
        while (fgets(buffer, sizeof(buffer), file))
        {
            ret = read_int(buffer, 1, &db[employee_counter].id);
            ret = read_int(buffer, 2, &db[employee_counter].salary);
            ret = read_string(buffer, 1, db[employee_counter].fname);
            ret = read_string(buffer, 2, db[employee_counter].lname);
            employee_counter++;
        }

        if (feof(file)) // hit end of file
        {
            close_file();
        }
    }
}

// return all employees with the last name used for the search.
int LookupLName2 (struct employee arr[], int n, char* name)
{
    int i, h, s;
    int check = -1;
    char testname1[MAXNAME], testname2[MAXNAME];

    s = strlen(name);
    for (i = 0; i < s; i++)
    {
        testname1[i] = tolower(name[i]);
    }

    printf("\nName\t\t\t\tSALARY\t   ID\n");
    printf("----------------------------------------------\n");
    for (i = 0; i < n; i++)
    {
        s = strlen(arr[i].lname);
        for (h = 0; h < s; h++)
        {
            testname2[h] = tolower(arr[i].lname[h]);
        }
        if (strcmp(testname1, testname2) == 0)
        {
            printf("%-15s\t%-15s\t%d\t%d\n", db[i].fname,db[i].lname,db[i].salary, db[i].id);
            check = 0;
        }
        memset(&testname2[0], 0, sizeof(testname2)); // clears the 'testname2' string for the next name
    }
    printf("----------------------------------------------\n");

    if (check == 0)
    {
        return check;
    }
    return check;
}


// Main function
int main(int argc, char *argv[])
{
    if (argc != 2) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf("usage: %s filename\n", argv[0]);
    }
    else
    {
        CreateDB(argv[1]);                   // Calls the function above to create the DB from the input data file
        SelectionSort(db, employee_counter); // Sorts the DB by Employee ID

        int choice;                // User's menu selection
        int x = 0;                 // employee location in DB
        int target_ID;             // target employee ID to search
        char target_name[MAXNAME]; // target name to search

        // Continue to display the DB menu until the user selects option '5' to quit
        while (1)
        {
            printf("\nEmployee DB Menu:\n");
            printf("----------------------------------\n");
            printf("\t(1) Print the Database\n");
            printf("\t(2) Lookup by ID\n");
            printf("\t(3) Lookup by Last Name\n");
            printf("\t(4) Add an Employee\n");
            printf("\t(5) Quit\n");
            printf("\t(6) Remove an Employee\n");
            printf("\t(7) Update Employee Record\n");
            printf("\t(8) Print Employee(s) with Highest Salary\n");
            printf("\t(9) Find all Employees with Entered Last Name\n");
            printf("----------------------------------\n");
            printf("Enter your choice: ");

            scanf("%d", &choice); // Read user choice for DB menu

            // Select the appropriate function based on user selection.
            switch (choice)
            {
            case 1:
                PrintDB(db, employee_counter);
                break;
            case 2:;
                int target_ID; // target employee ID to search
                printf("\nPlease enter an employee ID: ");
                scanf("%d", &target_ID);
                x = LookupID(db, 0, employee_counter, target_ID);
                if (x == -1)
                {
                    printf("\nUser with employee ID '%d' not found\n", target_ID);
                }
                else
                {
                    printf("\nName\t\t\t\tSALARY\t   ID\n");
                    printf("----------------------------------------------\n");
                    printf("%-15s\t%-15s\t%d\t%d\n", db[x].fname, db[x].lname, db[x].salary, db[x].id);
                    printf("----------------------------------------------\n");
                }

                break;
            case 3:
                printf("\nPlease enter an employee's last name: ");
                scanf("%s", target_name);
                x = LookupLName(db, employee_counter, target_name);
                if (x == -1)
                {
                    printf("\nUser with last name '%s' not found\n", target_name);
                }
                else
                {
                    printf("\nName\t\t\t\tSALARY\t   ID\n");
                    printf("----------------------------------------------\n");
                    printf("%-15s\t%-15s\t%d\t%d\n", db[x].fname, db[x].lname, db[x].salary, db[x].id);
                    printf("----------------------------------------------\n");
                }
                break;
            case 4:
                AddEmployee(db);
                break;
            case 5:
                printf("\nLater!\n\n");
                return 0;
                break;
            case 6:
                printf("\nPlease enter an employee ID: ");
                scanf("%d", &target_ID);
                x = LookupID(db, 0, employee_counter, target_ID);
                if (x == -1)
                {
                    printf("\nUser with employee ID '%d' not found\n", target_ID);
                }
                else
                {
                    RemoveEmployee(db, x);
                }
                break;
            case 7:
                printf("\nPlease enter an employee ID: ");
                scanf("%d", &target_ID);
                x = LookupID(db, 0, employee_counter, target_ID);
                if (x == -1)
                {
                    printf("\nUser with employee ID '%d' not found\n", target_ID);
                }
                else
                {
                    x = UpdateEmployee(db, x); // this function returns an int that isn't used
                }
                break;
            case 8:
                PrintHighestSalary(db, employee_counter);
                break;
            case 9:
                printf("\nPlease enter an employee's last name: ");
                scanf("%s", target_name);
                x = LookupLName2(db, employee_counter, target_name);
                if (x == -1)
                {
                    printf("\nUser with last name '%s' not found\n", target_name);
                }
                break;
            default:
                printf("\nInvalid input. Please try again.\n");
                break;
            }
        }
    }
}