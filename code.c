#include <stdio.h>
#include <stdlib.h>

//define coffee contents for the type of coffee
#define espresso_beans 8
#define espresso_water 30
#define espresso_milk 0

#define cappuccino_beans 8
#define cappuccino_water 30
#define cappuccino_milk 70

#define mocha_beans 8
#define mocha_water 39
#define mocha_milk 160
#define mocha_chocolate 30

//define the threshold constants
//admin password
#define ADP 4532
#define threshold_beans 10
#define threshold_water 100
#define threshold_milk 50
#define threshold_chocolate 20

//declare global variables
//total sales price
float total_sales = 0.0;

//levels of ingredients
int coffee_beans = 100;
int water = 100;
int milk = 100;
int chocolate = 100;

//coffee prices
float espresso_price = 3.5;
float cappuccino_price = 4.5;
float mocha_price = 5.5;

//function declarations
void order_coffee();
void admin_mode();
void check_ingredients(int type);
void handle_payment(float coffeeprice);
void update_ingredients(int type);
void replenish_ingredients();
void change_coffee_price();
void summary();

int main() {
    int choice;

    //main menu loop
    while (1) {
        printf("Welcome! :\n");
        printf("[1] Order Coffee\n");
        printf("[2] Admin Mode access (only for admins)\n");
        printf("[3] Exit\n");
        printf("Choose option: ");
        scanf("%d", &choice);

        //handle user input for the main menu
        switch (choice) {
            case 1:
                //use coffee ordering function
                order_coffee();
                break;

            case 2:
                //use admin mode
                admin_mode();
                break;

            case 3:
                printf("Thank you for ordering.....exiting\n");
                //exit the code program
                return 0;

            default:
                printf("Invalid, please try again\n");
        }
    }
}


void check_ingredients(int type) {
    //ESPRESSO
    if (type == 1) {
        if (coffee_beans < espresso_beans || water < espresso_water) {
            printf("Espresso is no longer available due to insufficient ingredients.\n");
        }
    }
    else if (type == 2) {
    //CAPPUCCINO
        if (coffee_beans < cappuccino_beans || water < cappuccino_water || milk < cappuccino_milk) {
            printf("Cappuccino is no longer available due to insufficient ingredients.\n");
        }
    }
    else if (type == 3) {
    //MOCHA
        if (coffee_beans < mocha_beans || water < mocha_water || milk < mocha_milk || chocolate < mocha_chocolate) {
            printf("Mocha is no longer available due to insufficient ingredients.\n");
        }
    }
}


void order_coffee() {
    int choice;
    float coffeeprice;
    char confirmation;

    //loop for ordering the coffee
    while (1) {
        printf("\nAvailable Coffee Types:\n");
        printf("1. -- ESPRESSO -- AED %.2f\n", espresso_price);
        printf("2. -- CAPPUCCINO -- AED %.2f\n", cappuccino_price);
        printf("3. -- MOCHA -- AED %.2f\n", mocha_price);
        printf("0. --Exit --\n");
        printf("Please choose the type of coffee you would like to order: ");
        scanf("%d", &choice);

        //exit ordering coffee if user selects 0
        if (choice == 0) {
            return;
        }

        //check ingredient availability for the selected coffee
        check_ingredients(choice);

        //determine the price based on the selected coffee
        if (choice == 1 && coffee_beans >= espresso_beans && water >= espresso_water) {
            coffeeprice = espresso_price;
        }
        else if (choice == 2 && coffee_beans >= cappuccino_beans && water >= cappuccino_water && milk >= cappuccino_milk) {
            coffeeprice = cappuccino_price;
        }
        else if (choice == 3 && coffee_beans >= mocha_beans && water >= mocha_water && milk >= mocha_milk && chocolate >= mocha_chocolate) {
            coffeeprice = mocha_price;
        }
        else {
            printf("Chosen coffee type is not available at the moment, please select another.\n");
            continue;
        }

        //ask for confirmation before proceeding with the order
        printf("You selected: ");
        if (choice == 1) {
            printf("Espresso\n");
        } else if (choice == 2) {
            printf("Cappuccino\n");
        } else if (choice == 3) {
            printf("Mocha\n");
        }

        printf("Are you sure you want to proceed? (y/n): ");
        //the space before %c to ignore previous newline
        scanf(" %c", &confirmation);

        if (confirmation == 'y' || confirmation == 'Y') {
            //handle the payment for the coffee
            handle_payment(coffeeprice);
            //update the ingredient levels
            update_ingredients(choice);
            //exit after successful order
            break;
        } else {
            printf("Order canceled. Please choose again.\n");
        }
    }
}


void handle_payment(float coffeeprice) {
    float payment;
    float totalpaid = 0.0;

    //loop to handle coin input
    while (totalpaid < coffeeprice) {
        printf("Insert 1 $ or 0.5 $ coins: ");
        scanf("%f", &payment);

        //validate the coin and add it to the total
        if (payment == 1.0 || payment == 0.5) {
            totalpaid += payment;
        }
        else {
            printf("Invalid coin, please try again.\n");
        }
    }

    printf("Payment successful, total payment is AED %.2f\n", totalpaid);

    //calculate and return change if needed
    float change = totalpaid - coffeeprice;
    if (change > 0) {
        printf("Your change is $ %.2f\n", change);
    }
    //update total sales
    total_sales += coffeeprice;
}


void update_ingredients(int type) {
    // ESPRESSO
    if (type == 1) {
        coffee_beans -= espresso_beans;
        water -= espresso_water;
    }
    // CAPPUCCINO
    else if (type == 2) {
        coffee_beans -= cappuccino_beans;
        water -= cappuccino_water;
        milk -= cappuccino_milk;
    }
    // MOCHA
    else if (type == 3) {
        coffee_beans -= mocha_beans;
        water -= mocha_water;
        milk -= mocha_milk;
        chocolate -= mocha_chocolate;
    }

    //send an alert if any ingredient is low
    if (coffee_beans <= threshold_beans) {
        printf("Alert: Low on Coffee Beans!\n");
    }
    if (water <= threshold_water) {
        printf("Alert: Low on Water!\n");
    }
    if (milk <= threshold_milk) {
        printf("Alert: Low on Milk!\n");
    }
    if (chocolate <= threshold_chocolate) {
        printf("Alert: Low on Chocolate Syrup!\n");
    }
}


void replenish_ingredients() {
    //replenish ingredients with random amounts between 500 and 1099
    coffee_beans = rand() % 600 + 500;
    water = rand() % 600 + 500;
    milk = rand() % 600 + 500;
    chocolate = rand() % 600 + 500;
    printf("Replenished the ingredients!\n");
}


void change_coffee_price() {
    int choice;
    float newprice;

    printf("\n Select the coffee type you want to change the price of:\n");
    printf("1. ESPRESSO\n");
    printf("2. CAPPUCCINO\n");
    printf("3. MOCHA\n");
    printf("0. Exit\n");
    printf("Select a coffee type: ");
    scanf("%d", &choice);

    //get the new price based on the coffee type
    switch (choice) {
        case 1:
            printf("Enter new price for Espresso: ");
            scanf("%f", &newprice);
            espresso_price = newprice;
            printf("Updated espresso cost to $ %.2f\n", espresso_price);
            break;

        case 2:
            printf("Enter new price for Cappuccino: ");
            scanf("%f", &newprice);
            cappuccino_price = newprice;
            printf("Updated cappuccino cost $ %.2f\n", cappuccino_price);
            break;

        case 3:
            printf("Enter new price for Mocha: ");
            scanf("%f", &newprice);
            mocha_price = newprice;
            printf("Updated mocha cost $ %.2f\n", mocha_price);
            break;

        case 0:
            return;

        default:
            printf("Invalid option, please try again.\n");
    }
}


void summary() {
    printf("\nCurrent Ingredients:\n");
    printf("Coffee Beans: %d grams\n", coffee_beans);
    printf("Water: %d milliliters\n", water);
    printf("Milk: %d milliliters\n", milk);
    printf("Chocolate Syrup: %d milliliters\n", chocolate);
    printf("Total Sales Amount: AED %.2f\n", total_sales);
}


void admin_mode() {
    int password;

    printf("Enter admin password: ");
    //input admin password
    scanf("%d", &password);

    //validate password
    if (password == ADP) {
        int choice;

        //admin menu loop
        while (1) {
            printf("\nAdmin Menu:\n");
            printf("[1] Replenish Ingredients\n");
            printf("[2] Change Coffee Prices\n");
            printf("[3] Display Ingredients and Total Sales\n");
            printf("[0] Exit Admin Mode\n");
            printf("Choose option: ");
            scanf("%d", &choice);

            //handle admin operations
            switch (choice) {
                case 1:
                    //replenishes the ingredients
                    replenish_ingredients();
                    break;

                case 2:
                    //changes the coffee prices
                    change_coffee_price();
                    break;

                case 3:
                    //shows the summary of ingredients and sales
                    summary();
                    break;

                case 0:
                    printf("Exiting Admin Mode....\n");
                    //exits admin mode
                    return;

                default:
                    printf("Invalid option, please try again.\n");
            }
        }
    }
    else {
        //shows invalid password input
        printf("Incorrect password! Denied access \n");
    }
}

