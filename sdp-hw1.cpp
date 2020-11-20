// sdp-hw1.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include <string>
#include <fstream>
#include <queue>

struct Operation {
    int floor;
    int time;
    int type; //0 is call 1 is go
    std::string direction;
};

class Elevator {
    int size;
    int currentOccupance;
    int currentFloor;
    int currentDest;
    int timeUntilLastStop;
    int currentStatus;
    std::queue<Operation> operations;

public:
    Elevator(int size_) {
        size = size_;
        currentOccupance = 0;
        currentFloor = 1;
        currentDest = 1;
        timeUntilLastStop = 0;
    }

    int getDest() {
        return currentDest;
    }

    int personEnters() {
        if (currentOccupance + 1 >= size) {
            return -1;
        }

        currentOccupance++;
    }

    void personLeaves() {
        currentOccupance--;
    }
    
    void addOperation(Operation op) {
        operations.push(op);
    }

    int getCurrentFloor() {
        return currentFloor;
    }

    bool done() {
        return operations.size() == 0;
    }

    bool isFull() {
        return currentOccupance == size;
    }

    int getCurrnetOccupance() {
        return currentOccupance;
    }

    void update(int time) {
        if (done()) {
            return;
        }

        Operation current = operations.front();

        int time_delta = time - current.time;

        int floorsMoved = time_delta % 5;

        currentFloor += floorsMoved;
        timeUntilLastStop += time_delta;

        if (currentFloor == currentDest) {
            timeUntilLastStop = 0;

            if (current.type == 0) {
                currentOccupance++;
            }
            else {
                currentOccupance--;
            }

            operations.pop();

            currentDest = operations.front().floor;
        }

    }

};

int main()
{
 
    std::string filename;

    std::cin >> filename;
    std::ifstream file (filename);

    int F;
    int L;
    int S;
    int R;

    if (!file.is_open()) {
        throw std::invalid_argument("File not Found!");
    }

    file >> F >> L >> S >> R;

    Elevator el1(L);
    Elevator el2(S);
        

    std::queue<Operation> operations;

    for (int i = 0; i < R; i++) {
        std::string type;

        std::string dir = "";

        int floor, time;
            
        if (i % 2 == 0) {
            file >> type >> dir >> floor >> time;
        }
        else {
            file >> type >> floor >> time;
        }

        struct Operation op = { floor, time, i % 2 != 0,  dir};

        operations.push(op);

    }


    // SIMULATION
    int step = 1;

    int currentTime = 0;

    Operation op;

    while (true) {

        op = operations.front();

        if (op.time >= currentTime) {
            
            int el1_direction = el1.getCurrentFloor() - el1.getDest();
            int el2_direction = el2.getCurrentFloor() - el2.getDest();

            int el1DistToOp = abs(el1.getCurrentFloor() - op.floor);
            int el2DistToOp = abs(el2.getCurrentFloor() - op.floor);

            if (el1.done() && el2.done()) {
                el1DistToOp > el2DistToOp ? el1.addOperation(op) : el2.addOperation(op);
                operations.pop();
            }

            if (el1.done()) {
                el1.addOperation(op);
                operations.pop();

            }

            if (el2.done()) {
                el2.addOperation(op);
                operations.pop();

            }

            bool useEl1 = false, useEl2 = false;

            if (!el1.isFull() &&
                ((el1.getCurrentFloor() <= op.floor && el1.getDest() >= op.floor && el1_direction < 0) ||
                 (el1.getCurrentFloor() >= op.floor && el1.getDest() <= op.floor && el1_direction > 0))) {
                useEl1 = true;
            }

            if (!el2.isFull() &&
                ((el2.getCurrentFloor() <= op.floor && el2.getDest() >= op.floor && el2_direction < 0) ||
                    (el2.getCurrentFloor() >= op.floor && el2.getDest() <= op.floor && el2_direction > 0))) {
                useEl2 = true;
            }

            if (useEl1 && useEl2) { 
                el1DistToOp > el2DistToOp ? el1.addOperation(op) : el2.addOperation(op);
                operations.pop();

            }
            else if (useEl1) {
                el1.addOperation(op);
                operations.pop();

            }
            else if(useEl2){
                el2.addOperation(op);
                operations.pop();

            }

        }

        currentTime += step;

        el1.update(currentTime);
        el2.update(currentTime);

    }
}