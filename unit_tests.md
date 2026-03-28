Unit Testing

Test Case 1: Successful Login
Command:
ssh user@server

Expected:
Result = Success stored in database.

Test Case 2: Failed Login
Command:
ssh wronguser@server

Expected:
Result = Failure stored in database.

Test Case 3: Brute Force Attack
Use tool:
hydra -l root -P passwords.txt ssh://server_ip

Expected:
Multiple failure logs stored.