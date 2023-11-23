#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

class Doctor
{
private:
    int id;
    int OPD_number;
    string name;
    string symptoms;
    string treatment;

public:
    void SetDetails()
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter the name of doctor: ";
        getline(cin, name);

        cout << "Enter the id of doctor: ";
        while (!(cin >> id) || id <= 0)
        {
            cout << "Invalid input. Enter a valid id: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Enter the OPD number: ";
        while (!(cin >> OPD_number) || OPD_number <= 0)
        {
            cout << "Invalid input. Enter a valid OPD number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter the symptoms: ";
        getline(cin, symptoms);

        cout << "Enter the treatment given: ";
        getline(cin, treatment);
    }

    void Display() const
    {
        cout << "Doctor Details:" << endl;
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "OPD Number: " << OPD_number << endl;
        cout << "Symptoms: " << symptoms << endl;
        cout << "Treatment Given: " << treatment << endl;
    }

    int GetID() const { return id; }
    int GetOPDNumber() const { return OPD_number; }
    string GetTreatment() const { return treatment; }

    friend istream& operator>>(istream& is, Doctor& doc);
};

class OPD
{
private:
    int OPD_num;
    string patient_name;
    string symptoms;
    string doctors_name;
    float fee;

public:
    void SetOPDDetails()
    {
        cout << "Enter the OPD number: ";
        while (!(cin >> OPD_num) || OPD_num <= 0)
        {
            cout << "Invalid input. Enter a valid OPD number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter the name of patient: ";
        getline(cin, patient_name);

        cout << "Enter symptoms: ";
        getline(cin, symptoms);

        cout << "Enter Doctor's name: ";
        getline(cin, doctors_name);

        cout << "Enter doctor's fee: ";
        while (!(cin >> fee) || fee <= 0)
        {
            cout << "Invalid input. Enter a valid fee: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    void OPDShow() const
    {
        cout << "OPD Details:" << endl;
        cout << "OPD number: " << OPD_num << endl;
        cout << "Patient Name: " << patient_name << endl;
        cout << "Symptoms: " << symptoms << endl;
        cout << "Doctor's Name: " << doctors_name << endl;
        cout << "Doctor's Fee: " << fee << endl;
    }

    int GetOPDNumber() const { return OPD_num; }
    int GetDoctorFee() const { return fee; }

    friend istream& operator>>(istream& is, OPD& opd);
};

istream& operator>>(istream& is, Doctor& doc)
{
    is >> doc.id >> doc.OPD_number;
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(is, doc.symptoms);
    getline(is, doc.treatment);

    return is;
}

istream& operator>>(istream& is, OPD& opd)
{
    is >> opd.OPD_num;
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(is, opd.patient_name);
    getline(is, opd.symptoms);
    getline(is, opd.doctors_name);
    is >> opd.fee;

    return is;
}

class HospitalManagementSystem
{
private:
    vector<Doctor> doctors;
    vector<OPD> opdRecords;

public:
    void AddDoctor()
    {
        Doctor newDoctor;
        newDoctor.SetDetails();
        doctors.push_back(newDoctor);
    }

    void DisplayDoctors() const
    {
        for (const auto& doctor : doctors)
        {
            doctor.Display();
            cout << "------------------------" << endl;
        }
    }

    void AddOPDRecord()
    {
        OPD newOPD;
        newOPD.SetOPDDetails();
        opdRecords.push_back(newOPD);
    }

    void DisplayOPDRecords() const
    {
        for (const auto& opd : opdRecords)
        {
            opd.OPDShow();
            cout << "------------------------" << endl;
        }
    }

    void SaveData()
    {
        ofstream file("hospital_data.txt");

        if (file.is_open())
        {
            for (const auto& doctor : doctors)
            {
                file << "Doctor\n";
                file << doctor.GetID() << "\n";
                file << doctor.GetOPDNumber() << "\n";
                file << doctor.GetTreatment() << "\n";
            }

            for (const auto& opd : opdRecords)
            {
                file << "OPD\n";
                file << opd.GetOPDNumber() << "\n";
                file << opd.GetDoctorFee() << "\n";
            }

            file.close();
        }
        else
        {
            cout << "Unable to save data." << endl;
        }
    }

    void LoadData()
    {
        ifstream file("hospital_data.txt");

        if (file.is_open())
        {
            string type;

            while (file >> type)
            {
                if (type == "Doctor")
                {
                    Doctor newDoctor;
                    file >> newDoctor;
                    doctors.push_back(newDoctor);
                }
                else if (type == "OPD")
                {
                    OPD newOPD;
                    file >> newOPD;
                    opdRecords.push_back(newOPD);
                }
            }

            file.close();
        }
        else
        {
            cout << "No previous data found." << endl;
        }
    }
};

int main()
{
    HospitalManagementSystem hospital;

    int choice;
    int numDoctors, numOPD;

    hospital.LoadData(); // Load existing data

    do
    {
        cout << "Hospital Management System" << endl;
        cout << "1. Add Doctor" << endl;
        cout << "2. Display Doctors" << endl;
        cout << "3. Add OPD Record" << endl;
        cout << "4. Display OPD Records" << endl;
        cout << "5. Save Data" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the number of doctors: ";
            cin >> numDoctors;
            for (int i = 0; i < numDoctors; ++i)
            {
                hospital.AddDoctor();
            }
            break;

        case 2:
            hospital.DisplayDoctors();
            break;

        case 3:
            cout << "Enter the number of OPD records: ";
            cin >> numOPD;
            for (int i = 0; i < numOPD; ++i)
            {
                hospital.AddOPDRecord();
            }
            break;

        case 4:
            hospital.DisplayOPDRecords();
            break;

        case 5:
            hospital.SaveData();
            cout << "Data saved successfully." << endl;
            break;

        case 0:
            cout << "Exiting program." << endl;
            break;

        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
        }

    } while (choice != 0);

    return 0;
}
