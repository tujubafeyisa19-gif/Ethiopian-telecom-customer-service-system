#include<iostream>
#include<string>
#include using namespace std; 
const int MAX_REGIONS = 12; 
const int MAX_CITIES = 100;
 const int MAX_BRANCHES = 1000; 
const int MAX_CUSTOMERS = 100000;

// Region Data string regionNames[MAX_REGIONS]; 
int citiesPerRegion[MAX_REGIONS];

string cityNames[MAX_CITIES]; 
int branchesPerCity[MAX_CITIES];

string branchNames[MAX_BRANCHES]; 
int customersPerBranch[MAX_BRANCHES];

int custIDs[MAX_CUSTOMERS]; 
string custNames[MAX_CUSTOMERS];

double custBalances[MAX_CUSTOMERS]; 
double custData[MAX_CUSTOMERS]; 
int custCalls[MAX_CUSTOMERS]; 
int custSMS[MAX_CUSTOMERS];

int regionCustomerCount[MAX_REGIONS] = {0}; int cityCustomerCount[MAX_CITIES] = {0};

// Tracking arrays for the reporting logic int cityRegion[MAX_CITIES];
int branchCity[MAX_BRANCHES];
int customerBranch[MAX_CUSTOMERS];
double cityUsage[MAX_CITIES] = {0.0};

int main() { cout << "=============== Ethiopian Telecom Customer Service System =============" << endl;

int numRegions;
cout << "Enter number of Regions: ";
cin >> numRegions;

// Simple Input Validation for Regions
while (numRegions <= 0 || numRegions > MAX_REGIONS)
{
    cout << "Invalid! Enter a number between 1 and " << MAX_REGIONS << ": ";
    cin >> numRegions;
}

int cityIndex = 0;
int branchIndex = 0;
int customerIndex = 0;

for (int r = 0; r < numRegions; r++)
{
    cout << "\nEnter Region Name: ";
    cin >> regionNames[r];

    cout << "Number of Cities: ";
    cin >> citiesPerRegion[r];

    // Simple Input Validation for Cities Count
    while (citiesPerRegion[r] < 0)
    {
        cout << "Number of cities cannot be negative. Try again: ";
        cin >> citiesPerRegion[r];
    }

    for (int c = 0; c < citiesPerRegion[r]; c++)
    {
        // Array boundary safety check
        if (cityIndex >= MAX_CITIES) {
            cout << "[Warning] System cannot hold more cities. Skipping.\n";
            break;
        }

        cout << "\nEnter City Name: ";
        cin >> cityNames[cityIndex];
        
        cityRegion[cityIndex] = r; 

        cout << "Number of Branches: ";
        cin >> branchesPerCity[cityIndex];

        // Simple Input Validation for Branches Count
        while (branchesPerCity[cityIndex] < 0)
        {
            cout << "Number of branches cannot be negative. Try again: ";
            cin >> branchesPerCity[cityIndex];
        }

        for (int b = 0; b < branchesPerCity[cityIndex]; b++)
        {
            // Array boundary safety check
            if (branchIndex >= MAX_BRANCHES) {
                cout << "[Warning] System cannot hold more branches. Skipping.\n";
                break;
            }

            cout << "\nEnter Branch Name: ";
            cin >> branchNames[branchIndex];
            
            branchCity[branchIndex] = cityIndex; 

            cout << "Number of Customers: ";
            cin >> customersPerBranch[branchIndex];

            // Simple Input Validation for Customers Count
            while (customersPerBranch[branchIndex] < 0)
            {
                cout << "Number of customers cannot be negative. Try again: ";
                cin >> customersPerBranch[branchIndex];
            }

            cityCustomerCount[cityIndex] += customersPerBranch[branchIndex];
            regionCustomerCount[r] += customersPerBranch[branchIndex];

            for (int cust = 0; cust < customersPerBranch[branchIndex]; cust++)
            {
                // Array boundary safety check
                if (customerIndex >= MAX_CUSTOMERS) {
                    cout << "[Warning] System cannot hold more customers. Skipping.\n";
                    break;
                }

                customerBranch[customerIndex] = branchIndex;

                cout << "\nCustomer ID: ";
                cin >> custIDs[customerIndex];
                while (custIDs[customerIndex] < 0)
                {
                    cout << "ID cannot be negative. Try again: ";
                    cin >> custIDs[customerIndex];
                }

                cout << "Customer Name: ";
                cin >> custNames[customerIndex];

                cout << "Balance: ";
                cin >> custBalances[customerIndex];
                while (custBalances[customerIndex] < 0)
                {
                    cout << "Balance cannot be negative. Try again: ";
                    cin >> custBalances[customerIndex];
                }

                cout << "Data Usage (MB): ";
                cin >> custData[customerIndex];
                while (custData[customerIndex] < 0)
                {
                    cout << "Data usage cannot be negative. Try again: ";
                    cin >> custData[customerIndex];
                }

                cout << "Call Minutes: ";
                cin >> custCalls[customerIndex];
                while (custCalls[customerIndex] < 0)
                {
                    cout << "Call minutes cannot be negative. Try again: ";
                    cin >> custCalls[customerIndex];
                }

                cout << "SMS Count: ";
                cin >> custSMS[customerIndex];
                while (custSMS[customerIndex] < 0)
                {
                    cout << "SMS count cannot be negative. Try again: ";
                    cin >> custSMS[customerIndex];
                }

                cityUsage[cityIndex] += (custData[customerIndex] + custCalls[customerIndex] + custSMS[customerIndex]);
                customerIndex++;
            }
            branchIndex++;
        }
        cityIndex++;
    }
}

cout << "\n\n========== REPORT ==========\n";

// Regions
cout << "\n========== REGIONS ==========\n";
for (int i = 0; i < numRegions; i++)
{
    cout << "Region " << i + 1 << ": " << regionNames[i] << endl;
}

// Cities
cout << "\n========== CITIES ==========\n";
for (int i = 0; i < cityIndex; i++)
{
    cout << "City " << i + 1 << ": " << cityNames[i] << endl;
}

// Branches
cout << "\n========== BRANCHES ==========\n";
for (int i = 0; i < branchIndex; i++)
{
    cout << "Branch " << i + 1 << ": " << branchNames[i] << endl;
}

// Customers
cout << "\n========== CUSTOMER RECORDS ==========\n";
double totalData = 0;
int totalCalls = 0;
int totalSMS = 0;

for (int i = 0; i < customerIndex; i++)
{
    cout << "\nCustomer " << i + 1 << endl;
    cout << "ID: " << custIDs[i] << endl;
    cout << "Name: " << custNames[i] << endl;
    cout << "Balance: " << custBalances[i] << endl;
    cout << "Data Usage: " << custData[i] << " MB" << endl;
    cout << "Call Minutes: " << custCalls[i] << endl;
    cout << "SMS Count: " << custSMS[i] << endl;

    totalData += custData[i];
    totalCalls += custCalls[i];
    totalSMS += custSMS[i];
}

// Customers per Region
cout << "\n========== CUSTOMERS IN EACH REGION ==========\n";
for (int i = 0; i < numRegions; i++)
{
    cout << regionNames[i] << " : " << regionCustomerCount[i] << " customers" << endl;
}

// Customers per City
cout << "\n========== CUSTOMERS IN EACH CITY ==========\n";
for (int i = 0; i < cityIndex; i++)
{
    cout << cityNames[i] << " : " << cityCustomerCount[i] << " customers" << endl;
}

// Customers per Branch
cout << "\n========== CUSTOMERS IN EACH BRANCH ==========\n";
int totalCustomers = 0;
for (int i = 0; i < branchIndex; i++)
{
    cout << branchNames[i] << " : " << customersPerBranch[i] << " customers" << endl;
    totalCustomers += customersPerBranch[i];
}

// Summary
cout << "\n========== SUMMARY ==========\n";
cout << "Total Customers Nationwide: " << totalCustomers << endl;
cout << "Total Data Usage: " << totalData << " MB" << endl;
cout << "Total Call Usage: " << totalCalls << " Minutes" << endl;
cout << "Total SMS Usage: " << totalSMS << endl;

int maxRegion = 0;
for(int i = 1; i < numRegions; i++)
{
    if(regionCustomerCount[i] > regionCustomerCount[maxRegion])
    {
        maxRegion = i;
    }
}
cout << "\nRegion with Highest Number of Customers: "
     << regionNames[maxRegion]
     << " (" << regionCustomerCount[maxRegion]
     << " customers)" << endl;

cout << "\n\n===== CITY WITH HIGHEST SERVICE USAGE IN EACH REGION =====\n";
for(int r = 0; r < numRegions; r++)
{
    int bestCity = 0;
    double maxUsage = -1.0; 
    bool foundAnyCity = false;

    for(int c = 0; c < cityIndex; c++)
    {
        if(cityRegion[c] == r)
        {
            if(foundAnyCity == false) 
            {
                maxUsage = cityUsage[c];
                bestCity = c;
                foundAnyCity = true; 
            }
            else if(cityUsage[c] > maxUsage)
            {
                maxUsage = cityUsage[c];
                bestCity = c;
            }
        }
    }
    if(foundAnyCity == true)
    {
        cout << "Region: " << regionNames[r] << " -> City: " << cityNames[bestCity]
             << " (Usage = " << cityUsage[bestCity] << ")" << endl;
    }
}
cout << "\n\n===== BRANCH WITH HIGHEST CUSTOMERS IN EACH CITY =====\n";
for(int c = 0; c < cityIndex; c++)
{
    int bestBranch = 0;
    int maxCustomers = -1;
    bool foundAnyBranch = false;

    for(int b = 0; b < branchIndex; b++)
    {
        if(branchCity[b] == c)
        {
            if(foundAnyBranch == false)
            {
                maxCustomers = customersPerBranch[b];
                bestBranch = b;
                foundAnyBranch = true;
            }
            else if(customersPerBranch[b] > maxCustomers)
            {
                maxCustomers = customersPerBranch[b];
                bestBranch = b;
            }
        }
    }
    if(foundAnyBranch == true)
    {
        cout << "City: " << cityNames[c] << " -> Branch: " << branchNames[bestBranch]
             << " (" << customersPerBranch[bestBranch] << " customers)" << endl;
    }
}

cout << "\n\n===== CUSTOMER WITH HIGHEST BALANCE IN EACH BRANCH =====\n";
for(int b = 0; b < branchIndex; b++)
{
    int bestCustomer = 0;
    double maxBalance = -1.0;
    bool foundAnyCustomer = false;

    for(int c = 0; c < customerIndex; c++)
    {
        if(customerBranch[c] == b)
        {
            if(foundAnyCustomer == false)
            {
                maxBalance = custBalances[c];
                bestCustomer = c;
                foundAnyCustomer = true;
            }
            else if(custBalances[c] > maxBalance)
            {
                maxBalance = custBalances[c];
                bestCustomer = c;
            }
        }
    }
    if(foundAnyCustomer == true)
    {
        cout << "Branch: " << branchNames[b] << " -> Customer: " << custNames[bestCustomer]
             << " (Balance = " << custBalances[bestCustomer] << ")" << endl;
    }
}

double averageBalance = 0;
double averageData = 0;
double averageCalls = 0;

// Division by Zero Prevention Check
if(customerIndex > 0)
{
    double totalBalance = 0;
    for(int i = 0; i < customerIndex; i++)
    {
        totalBalance += custBalances[i];
    }
    averageBalance = totalBalance / customerIndex;
    averageData = totalData / customerIndex;
    averageCalls = (double)totalCalls / customerIndex;
}

cout << "\n===== NATIONAL STATISTICS =====\n";
cout << "Average Mobile Balance per Customer: "<< averageBalance << endl;
cout << "Average Data Usage per Customer: "<< averageData << " MB" << endl;
cout << "Average Call Usage per Customer: "<< averageCalls << " Minutes" << endl;
cout << "Total Number of Branches Nationwide: "<< branchIndex << endl;

cout << "\n\n========== HIERARCHICAL CUSTOMER SERVICE REPORT ==========\n";

cout << "\n===== NATIONAL TELECOM STATISTICS =====\n";
cout << "Total Regions: " << numRegions << endl;
cout << "Total Cities: " << cityIndex << endl;
cout << "Total Branches: " << branchIndex << endl;
cout << "Total Customers: " << customerIndex << endl;
cout << "Total Data Usage: " << totalData << " MB" << endl;
cout << "Total Call Usage: " << totalCalls << " Minutes" << endl;
cout << "Total SMS Usage: " << totalSMS << endl;

cout << "\n===== REGIONAL SUMMARIES =====\n";
for(int r = 0; r < numRegions; r++)
{
    cout << "\nRegion: "<< regionNames[r] << endl;
    cout << "Customers: "<< regionCustomerCount[r]<< endl;
}

cout << "\n===== CUSTOMER DISTRIBUTION =====\n";
for(int r = 0; r < numRegions; r++)
{
    cout << "\nRegion: "<< regionNames[r]<< endl;
    
    for(int c = 0; c < cityIndex; c++)
    {
        if(cityRegion[c] == r)
        {
            cout << "   City: " << cityNames[c] << " ("<< cityCustomerCount[c]<< " customers)"<< endl;

            for(int b = 0; b < branchIndex; b++)
            {
                if(branchCity[b] == c)
                {
                    cout << "      Branch: "<< branchNames[b] << " ("<< customersPerBranch[b]<< " customers)"<< endl;
                }
            }
        }
    }
}

cout << "\n===== BRANCH LEVEL SUMMARIES =====\n";
for(int b = 0; b < branchIndex; b++)
{
    int customerCount = 0;
    double branchData = 0;
    int branchCalls = 0;
    int branchSMS = 0;

    for(int c = 0; c < customerIndex; c++)
    {
        if(customerBranch[c] == b)
        {
            customerCount++;
            branchData += custData[c];
            branchCalls += custCalls[c];
            branchSMS += custSMS[c];
        }
    }
  
    cout << "\nBranch: "<< branchNames[b]<< endl;
    cout << "Customers: "<< customerCount<< endl;
    cout << "Data Usage: "<< branchData<< " MB" << endl;
    cout << "Call Usage: "<< branchCalls<< " Minutes" << endl;
    cout << "SMS Usage: "<< branchSMS<< endl;
}

cout << "\n===== SERVICE USAGE STATISTICS =====\n";
double avgData = 0;
double avgCalls = 0;
double avgBalance = 0;
double totalBalance = 0;

for(int i = 0; i < customerIndex; i++)
{
    totalBalance += custBalances[i];
}

// Division by Zero Prevention Check
if(customerIndex > 0)
{
    avgData = totalData / customerIndex;
    avgCalls = (double)totalCalls / customerIndex;
    avgBalance = totalBalance / customerIndex;
}

cout << "Average Mobile Balance: "<< avgBalance<< endl;
cout << "Average Data Usage: "<< avgData<< " MB" << endl;
cout << "Average Call Usage: "<< avgCalls<< " Minutes" << endl;

return 0;
}