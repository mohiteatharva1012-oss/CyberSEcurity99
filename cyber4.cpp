#include <bits/stdc++.h>
#include <openssl/sha.h>   // For hashing (use bcrypt/Argon2 in real apps)
using namespace std;

// Simple SHA256 hashing function (demo only)
string sha256(const string &input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)input.c_str(), input.size(), hash);
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    return ss.str();
}

// User database (in-memory for demo)
map<string, string> users; // username -> hashed password
map<string, bool> sessions; // username -> logged in

// Registration
void registerUser(const string &username, const string &password) {
    if (users.count(username)) {
        cout << "User already exists!\n";
        return;
    }
    users[username] = sha256(password);
    cout << "Registration successful!\n";
}

// Login
bool loginUser(const string &username, const string &password) {
    if (!users.count(username)) {
        cout << "User not found!\n";
        return false;
    }
    if (users[username] == sha256(password)) {
        sessions[username] = true;
        cout << "Login successful!\n";
        return true;
    } else {
        cout << "Invalid password!\n";
        return false;
    }
}

// Logout
void logoutUser(const string &username) {
    if (sessions[username]) {
        sessions[username] = false;
