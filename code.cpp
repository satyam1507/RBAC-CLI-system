#include <bits/stdc++.h>
using namespace std;

class Resources
{
public:
    void addResource(string resource)
    {
        resources.insert(resource);
    }

    bool checkResourceExists(string resource)
    {
        return resources.find(resource) != resources.end();
    }

private:
    set<string> resources;
};

class Access
{
public:
    void addAccessType(string accessType)
    {
        accessTypes.insert(accessType);
    }

    bool checkAccessTypeExists(string accessType)
    {
        return accessTypes.find(accessType) != accessTypes.end();
    }

private:
    set<string> accessTypes;
};

class Roles
{
public:
    void addRole(string role)
    {
        roles.insert(role);
    }

    bool checkRoleExists(string role)
    {
        return roles.find(role) != roles.end();
    }

private:
    set<string> roles;
};

class Users
{
public:
    void addUser(string user)
    {
        users.insert(user);
    }

    bool checkUserExists(string user)
    {
        return users.find(user) != users.end();
    }

private:
    set<string> users;
};

class Assignments
{
public:
    void assignAccessToResource(string accessType, string resource)
    {
        accessOnResources[resource].insert(accessType);
    }

    void assignAccessToRoleOnResource(string accessType, string resource, string role)
    {
        accessOnResourcesToRoles[resource][role].insert(accessType);
    }

    void assignRoleToUser(string role, string user)
    {
        rolesToUsers[user].insert(role);
    }

    bool checkUserHasAccessOnResource(string user, string resource, string accessType)
    {
        set<string> roles = rolesToUsers[user];
        for (string role : roles)
        {
            set<string> accessTypes = accessOnResourcesToRoles[resource][role];
            if (accessTypes.find(accessType) != accessTypes.end())
            {
                return true;
            }
        }
        return false;
    }

private:
    map<string, set<string>> accessOnResources;
    map<string, map<string, set<string>>> accessOnResourcesToRoles;
    map<string, set<string>> rolesToUsers;
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    // Initialize classes
    Resources resources;
    Access access;
    Roles roles;
    Users users;
    Assignments assignments;

    while (true)
    {
        cout << "Enter command: ";
        string command;
        getline(cin, command);

        // Parse command and arguments
        stringstream ss(command);
        string cmd;
        ss >> cmd;

        // addResource command
        if (cmd == "addResource")
        {
            string resource;
            ss >> resource;
            resources.addResource(resource);
            cout << "Creates a resource called " << resource << endl;
        }
        // addAccess command
        else if (cmd == "addAccess")
        {
            string accessType;
            ss >> accessType;
            access.addAccessType(accessType);
            cout << "Creates universal access " << accessType << endl;
        }
        // addRole command
        else if (cmd == "addRole")
        {
            string role;
            ss >> role;
            roles.addRole(role);
            cout << "Creates a role called " << role << endl;
        }
        // addUser command
        else if (cmd == "addUser")
        {
            string user;
            ss >> user;
            users.addUser(user);
            cout << "Creates a user called " << user << endl;
        }
        // addAccessOnResource command
        else if (cmd == "addAccessOnResource")
        {
            string accessType, resource;
            ss >> accessType >> resource;
            assignments.assignAccessToResource(accessType, resource);
            cout << "Creates " << accessType << " access on resource " << resource << endl;
        }
        // addAccessOnResourceToRole command
        else if (cmd == "addAccessOnResourceToRole")
        {
            string accessType, resource, role;
            ss >> accessType >> resource >> role;
            assignments.assignAccessToRoleOnResource(accessType, resource, role);
            // Creates READ access on Resource IMAGE for role ADMIN
            cout << "Creates " << accessType << " access on resource " << resource << " for role " << role << endl;
        }
        // addRoleToUser command
        else if (cmd == "addRoleToUser")
        {
            string role, user;
            ss >> role >> user;
            assignments.assignRoleToUser(role, user);
            cout << "Role " << role << " added to user " << user << endl;
        }
        // checkAccess command
        else if (cmd == "checkAccess")
        {
            string user, resource, accessType;
            ss >> user >> resource >> accessType;
            if (users.checkUserExists(user) && resources.checkResourceExists(resource) && access.checkAccessTypeExists(accessType))
            {
                if (assignments.checkUserHasAccessOnResource(user, resource, accessType))
                {
                    cout << "Yes, user has " << accessType << " access on resource " << resource << endl;
                }
                else
                {
                    cout << "No, user does not have " << accessType << " access on resource " << resource << endl;
                }
            }
            else
            {
                cout << "Invalid command" << endl;
            }
        }
        else if (cmd == "Exit"||cmd == "exit"||cmd == "Stop"||cmd == "stop")
        {
            cout << "Program Stopped" << endl;
            break;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }
}
