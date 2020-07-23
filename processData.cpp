/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : student code for Assignment 1 - Data structures and Algorithms - Spring 2018
 * =========================================================================================
 */
#include "requestLib.h"
#include "dbLib.h"

#define MAX_LENGTH_TIMESTAMP    20
#define START                   -1e-5
#define ZERO                    0e-5
#define STOP                    5e-3

struct Data {
    L1List<L1List<VRecord>> NewDataList;
    int flag;
};

/// Initialize and Finalize any global data that you use in the program
bool _CopyLinkedList(L1List<VRecord>& recList, L1List<VRecord>& CopyList) {
    if(recList.getpHead() == NULL) {
        return false;
    }
    else {
        L1Item<VRecord>* pCurr = recList.getpHead();
        while(pCurr != NULL) {
            VRecord CopyData = pCurr->data;
            L1Item<VRecord>* CopyNode = new L1Item<VRecord>(CopyData);
            CopyList.insertHead(CopyNode);
            pCurr = pCurr->pNext;
        }
        CopyList.reverse();
        return true;
    }
}
bool _CCCCreateLinkedListID(L1List<VRecord>& recList, L1List<L1List<VRecord>> &NewDataList) {
    if(recList.getpHead() == NULL) {
        return false;
    }
    while(recList.getSize() > 0) {
        L1Item<VRecord>* Node = recList.getFirst();
        L1Item<L1List<VRecord>>* pCurr = NewDataList.getpHead();
        if(pCurr == NULL) {
            L1List<VRecord>* ListChild = new L1List<VRecord>();
            ListChild->insertHead(Node);
            L1Item<L1List<VRecord>>* Data = new L1Item<L1List<VRecord>>((*ListChild));
            NewDataList.insertHead(Data);
            pCurr = NewDataList.getpHead();
        }
        else {
            int flag = 0;
            while(pCurr != NULL) {
                if(strcmp(pCurr->data.getpHead()->data.id, Node->data.id) == 0) {
                    pCurr->data.insertLast(Node);
                    flag = 1;
                    break;
                }
                if(pCurr->pNext == NULL) {
                    break;
                }
                pCurr = pCurr->pNext;
            }
            if(pCurr->pNext == NULL && flag == 0) {
                L1List<VRecord>* db = new L1List<VRecord>();
                db->insertHead(Node);
                L1Item<L1List<VRecord>>* Data = new L1Item<L1List<VRecord>>((*db));
                pCurr->pNext = Data;
                NewDataList.increaseSize();
            }
        }
    }
}

bool _CreateLinkedListID(L1List<VRecord>& recList, L1List<L1List<VRecord>> &NewDataList) {
    if(recList.getpHead() == NULL) {
        return false;
    }
    while(recList.getSize()) {
        L1List<VRecord>* db = new L1List<VRecord>();
        L1Item<VRecord>* p = recList.getFirst();
        db->insertHead(p);

        int flag = 0;
        L1Item<VRecord>* pPrev = NULL;
        L1Item<VRecord>* pCurr = recList.getpHead();
        while(pCurr != NULL) {
            if(strcmp(pCurr->data.id, p->data.id) == 0) {
                L1Item<VRecord>* pTemp = NULL;
                if(flag == 0) {
                    pCurr = pCurr->pNext;
                    pTemp = recList.getFirst();
                }
                else {
                    pTemp = pCurr;
                    pPrev->pNext = pCurr->pNext;
                    pCurr = pCurr->pNext;
                    recList.decreaseSize();
                    flag++;
                }
                pTemp->pNext = NULL;
                db->insertHead(pTemp);
            }
            else {
                pPrev = pCurr;
                pCurr = pCurr->pNext;
                flag++;
            }
        }
        db->reverse();
        L1Item<L1List<VRecord>>* New = new L1Item<L1List<VRecord>>((*db));
        NewDataList.insertHead(New);
    }
    NewDataList.reverse();
    return true;
}

bool initVGlobalData(void** pGData) {
    // TODO: allocate global data if you think it is necessary.
    /// pGData contains the address of a pointer. You should allocate data for the global data
    /// and then assign its address to *pGData
    static Data* pGList = new Data;
    pGList->flag = 0;
    *pGData = pGList;
    return true;
}

void releaseVGlobalData(void* pGData) {
    // TODO: release the data if you finish using it
}
bool _processRequest(VRequest& request, L1List<L1List<VRecord>> &DoubleLinkedList, L1List<VRecord>& recList);
bool _Check(L1List<L1List<VRecord>> &DoubleLinkedList, L1List<VRecord>& recList);
bool processRequest(VRequest& request, L1List<VRecord>& recList, void* pGData) {
    // TODO: Your code comes here

    /// NOTE: The output of the request will be printed on one line
    /// end by the end-line '\n' character.

    Data* pGList = (Data*) pGData;
    L1List<VRecord> CopyLinkedList;
    
    if(pGList->flag == 0) {
        //_CopyLinkedList(recList, CopyLinkedList);
        _CreateLinkedListID(recList, pGList->NewDataList);
        pGList->flag++;
    }
    
    //return _processRequest(request, pGList->NewDataList, recList);
    _Check(pGList->NewDataList, recList);
    return true;

}
bool _Check(L1List<L1List<VRecord>> &DoubleLinkedList, L1List<VRecord>& recList) {
    //cout << DoubleLinkedList.getSize() << endl;
    L1Item<L1List<VRecord>>* pHead = DoubleLinkedList.getpHead();
    while(true) {
        if(strcmp(pHead->data.getpHead()->data.id, "51C65728") == 0) {
            cout << pHead->data.getSize() << endl;
            L1Item<VRecord>* pCurr = pHead->data.getpHead();
            while(pCurr != NULL) {
                printVRecord(pCurr->data);
                pCurr = pCurr->pNext;
            }
            break;
        }
        pHead = pHead->pNext;
    }
    return true;
}


bool _processRequest(VRequest& request, L1List<L1List<VRecord>> &DoubleLinkedList, L1List<VRecord>& recList) {
    
    if (!strncmp(request.code, "CNV", 3)) {
        if (strlen(request.code) > 3) {
            cout << request.code << ": not found!" << endl;
        }
        else {
            cout << request.code << ": " << DoubleLinkedList.getSize() << endl;
        }
    }

    else if (!strncmp(request.code, "VFF", 3)){
        if (strlen(request.code) > 3) {
            cout << request.code << ": not found!" << endl;
        }
        else {
            cout << request.code << ": " << DoubleLinkedList.getpHead()->data.getpHead()->data.id << endl;
        }
    }

    else if (!strncmp(request.code, "VFL", 3)){
        if (strlen(request.code) > 3) {
            cout << request.code << ": not found!" << endl;
        }
        else {
            L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
            while(pCurr->pNext != NULL) {
                pCurr = pCurr->pNext;
            }
            cout << request.code << ": " << pCurr->data.getpHead()->data.id << endl;
        }
    }

    else if (!strncmp(request.code, "VFY", 3)) {
        char* ID = getRequestID(request);
        L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
        while(pCurr != NULL) {
            if(strcmp(pCurr->data.getpHead()->data.id, ID) == 0) {
                cout << "VFY" << ID << ": " << pCurr->data.getpHead()->data.y << endl;
                break;
            }
            pCurr = pCurr->pNext;
        }
        if(pCurr == NULL) {
            cout << "VFY" << ID << ": not found!" << endl;
        }
    }

    else if (!strncmp(request.code, "VFX", 3)) {
        char* ID = getRequestID(request);
        L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
        while(pCurr != NULL) {
            if(strcmp(pCurr->data.getpHead()->data.id, ID) == 0) {
                cout << "VFX" << ID << ": " << pCurr->data.getpHead()->data.x << endl;
                break;
            }
            pCurr = pCurr->pNext;
        }
        if(pCurr == NULL) {
            cout << "VFX" << ID << ": not found!" << endl;
        }
    }

    else if (!strncmp(request.code, "VLY", 3)) {
        char* ID = getRequestID(request);
        L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
        while(pCurr != NULL) {
            if(strcmp(pCurr->data.getpHead()->data.id, ID) == 0) {
                L1Item<VRecord>* p = pCurr->data.getpHead();
                while(p->pNext != NULL) {
                    p = p->pNext;
                }
                cout << "VLY" << ID << ": " << p->data.y << endl;
                break;
            }
            pCurr = pCurr->pNext;
        }
        if(pCurr == NULL) {
            cout << "VLY" << ID << ": not found!" << endl;
        }
    }

    else if (!strncmp(request.code, "VLX", 3)) {
        char* ID = getRequestID(request);
        L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
        while(pCurr != NULL) {
            if(strcmp(pCurr->data.getpHead()->data.id, ID) == 0) {
                L1Item<VRecord>* p = pCurr->data.getpHead();
                while(p->pNext != NULL) {
                    p = p->pNext;
                }
                cout << "VLX" << ID << ": " << p->data.x << endl;
                break;
            }
            pCurr = pCurr->pNext;
        }
        if(pCurr == NULL) {
            cout << "VLX" << ID << ": not found!" << endl;
        }
    }

    else if (!strncmp(request.code, "VFT", 3)) {
        char* ID = getRequestID(request);
        char Buffer[MAX_LENGTH_TIMESTAMP];
        L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
        while(pCurr != NULL) {
            if(strcmp(pCurr->data.getpHead()->data.id, ID) == 0) {
                strPrintTime(Buffer, pCurr->data.getpHead()->data.timestamp);
                cout << "VFT" << ID << ": " << Buffer << endl;
                break;
            }
            pCurr = pCurr->pNext;
        }
        if(pCurr == NULL) {
            cout << "VFT<" << ID << ": not found!" << endl;
        }
    }

    else if (!strncmp(request.code, "VLT", 3)) {
        char* ID = getRequestID(request);
        char Buffer[MAX_LENGTH_TIMESTAMP];
        L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
        while(pCurr != NULL) {
            if(strcmp(pCurr->data.getpHead()->data.id, ID) == 0) {
                L1Item<VRecord>* p = pCurr->data.getpHead();
                while(p->pNext != NULL) {
                    p = p->pNext;
                }
                strPrintTime(Buffer, p->data.timestamp);
                cout << "VLT" << ID << ": " << Buffer << endl;
                break;
            }
            pCurr = pCurr->pNext;
        }
        if(pCurr == NULL) {
            cout << "VLT" << ID << ": not found!" << endl;
        }
    }

    else if (!strncmp(request.code, "VCR", 3)) {
        char* ID = getRequestID(request);
        L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
        while(pCurr != NULL) {
            if(strcmp(pCurr->data.getpHead()->data.id, ID) == 0) {
                cout << "VCR" << ID << ": " << pCurr->data.getSize() << endl;
                break;
            }
            pCurr = pCurr->pNext;
        }
        if(pCurr == NULL) {
            cout << "VCR" << ID << ": not found!" << endl;
        }
    }

    else if (!strncmp(request.code, "VCL", 3)) {
        char* ID = getRequestID(request);
        double S = ZERO;
        int Num_Record = 0;
        L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
        while(pCurr != NULL) {
            if(strcmp(pCurr->data.getpHead()->data.id, ID) == 0) {
                Num_Record = pCurr->data.getSize();
                L1Item<VRecord>* p = pCurr->data.getpHead();
                L1Item<VRecord>* pp = p->pNext;
                while(pp != NULL) {
                    double Sdd = distanceVR(p->data.y, p->data.x, pp->data.y, pp->data.x);
                    if(Sdd != ZERO) {
                        //cout << Sdd << endl;
                        S = S + Sdd;
                    }
                    p = pp;
                    pp = pp->pNext;
                }
                break;
            }
            pCurr = pCurr->pNext;
        }
        if(pCurr == NULL) {
            cout << "VCL" << ID << ": not found!" << endl;
        }
        else if(Num_Record == 1) {
            cout << "VCL" << ID << ": non stop!" << endl;
        }
        else {
            cout << "VCL" << ID << ": " << S << endl;
        }
    }

    else if (!strncmp(request.code, "VMT", 3)) {                ////////////////////////    
        char* ID = getRequestID(request);
        int Time = 0;
        int Num_Record = 0;
        L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
        while(pCurr != NULL) {
            if(strcmp(pCurr->data.getpHead()->data.id, ID) == 0) {
                Num_Record = pCurr->data.getSize();
                L1Item<VRecord>* p = pCurr->data.getpHead();
                L1Item<VRecord>* pp = p->pNext;
                //double Sdd = distanceVR(p->data.y, p->data.x, pp->data.y, pp->data.x);
                //cout << Sdd << endl;
                while(pp != NULL) {
                    double Sdd = distanceVR(p->data.y, p->data.x, pp->data.y, pp->data.x);
                    cout << p->data.x << "           " << p->data.y << endl;
                    cout << pp->data.x << "            " << pp->data.y << endl;
                    cout << Sdd * 1000 << "*******";
                    cout << difftime(pp->data.timestamp, p->data.timestamp) << endl;
                    if(Sdd >= STOP) {
                        Time = Time + difftime(pp->data.timestamp, p->data.timestamp);
                    }
                    p = pp;
                    pp = pp->pNext;
                }
                break;
            }
            pCurr = pCurr->pNext;
        }
        if(pCurr == NULL) {
            cout << "VMT" << ID << ": not found!" << endl;
        }
        else if(Num_Record == 1) {
            cout << "VMT" << ID << ": non stop!" << endl;
        }
        else {
            cout << "VMT" << ID << ": " << Time << endl;
        }
        
    }

    else if (!strncmp(request.code, "VFS", 3)) {                ////////////////////////
        char* ID = getRequestID(request);
        int Num_ZERO = 0;
        L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
        L1Item<VRecord>* pTemp = NULL;
        while(pCurr != NULL) {
            if(strcmp(pCurr->data.getpHead()->data.id, ID) == 0) {
                if(pCurr->data.getSize() > 1) {
                    L1Item<VRecord>* p = pCurr->data.getpHead();
                    L1Item<VRecord>* pp = p->pNext;
                    while(pp != NULL) {
                        if(distanceVR(p->data.y,p->data.x, pp->data.y, pp->data.x) <= STOP) {
                            pTemp = p;
                            Num_ZERO = 1;
                            break;
                        }
                        p = pp;
                        pp = pp->pNext;
                    }
                }
                break;
            }
            pCurr = pCurr->pNext;
        }
        if(pCurr == NULL) {
            cout << "VFS" << ID << ": not found!" << endl;
        }
        else if(Num_ZERO == 0) {
            cout << "VFS" << ID << ": non stop!" << endl;
        }
        else {
            cout << "VFS" << ID << ": " << "(" << pTemp->data.x << ", " << pTemp->data.y << ")" << endl;
        }
    }

    else if (!strncmp(request.code, "VLS", 3)) {
        char* ID = getRequestID(request);
        int Num_ZERO = 0;
        L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
        L1Item<VRecord>* pTemp = NULL;
        while(pCurr != NULL) {
            if(strcmp(pCurr->data.getpHead()->data.id, ID) == 0) {
                if(pCurr->data.getSize() > 1) {
                    L1Item<VRecord>* p = pCurr->data.getpHead();
                    L1Item<VRecord>* pp = p->pNext;
                    while(pp != NULL) {
                        if(distanceVR(p->data.y,p->data.x, pp->data.y, pp->data.x) <= STOP) {
                            pTemp = p;
                            Num_ZERO = 1;
                            //break;
                        }
                        p = pp;
                        pp = pp->pNext;
                    }
                }
                break;
            }
            pCurr = pCurr->pNext;
        }
        if(pCurr == NULL) {
            cout << "VLS" << ID << ": not found!" << endl;
        }
        else if(Num_ZERO == 0) {
            cout << "VLS" << ID << ": non stop!" << endl;
        }
        else {
            cout << "VLS" << ID << ": " << "(" << pTemp->data.x << ", " << pTemp->data.y << ")" << endl;
        }
    }

    else if (!strncmp(request.code, "VMS", 3)) {
        char* ID = getRequestID(request);
        int Time_ZERO = 0;
        int TimeCurrent = 0;
        int Num_Record = 0;
        L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
        while(pCurr != NULL) {
            if(strcmp(pCurr->data.getpHead()->data.id, ID) == 0) {
                Num_Record = pCurr->data.getSize();
                L1Item<VRecord>* p = pCurr->data.getpHead();
                L1Item<VRecord>* pp = p->pNext;
                while(pp != NULL) {
                    double Sdd = distanceVR(p->data.y, p->data.x, pp->data.y, pp->data.x);
                    if(Sdd <= STOP) {
                        TimeCurrent = TimeCurrent + difftime(p->data.timestamp, pp->data.timestamp);
                    }
                    else {
                        TimeCurrent = 0;
                    }
                    if(Time_ZERO < TimeCurrent) {
                        Time_ZERO = TimeCurrent;
                    }
                    p = pp;
                    pp = pp->pNext;
                }
                break;
            }
            pCurr = pCurr->pNext;
        }
        if(pCurr == NULL) {
            cout << "VMS" << ID << ": not found!" << endl;
        }
        else if(Num_Record == 1 || Time_ZERO == 0) {
            cout << "VMS" << ID << ": non stop!" << endl;
        }
        else {
            cout << "VMS" << ID << ": " << Time_ZERO << endl;
        }
    }

    else if (!strncmp(request.code, "VAS", 3)) {
        char* ID = getRequestID(request);
        L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
        double S_medium = ZERO;
        int Num_Record = 0;
        while(pCurr != NULL) {
            if(strcmp(pCurr->data.getpHead()->data.id, ID) == 0) {
                Num_Record = pCurr->data.getSize();
                if(Num_Record > 1){
                    double S = ZERO;
                    L1Item<VRecord>* p = pCurr->data.getpHead();
                    L1Item<VRecord>* pp = p->pNext;
                    while(pp != NULL) {
                        S = S + distanceVR(p->data.y, p->data.x, pp->data.y, pp->data.x);
                        p = pp;
                        pp = pp->pNext;
                    }
                    S_medium = S / (Num_Record - 1);
                }
                break;
            }
            pCurr = pCurr->pNext;
        }
        if(pCurr == NULL) {
            cout << "VAS" << ID << ": not found!" << endl;
        }
        else if(Num_Record == 1) {
            cout << "VAS" << ID << ": non stop!" << endl;
        }
        else {
            S_medium = S_medium * 1000;
            cout << "VAS" << ID << ": " << S_medium << " meter" << endl;
        }
    }

    else if (!strncmp(request.code, "MST", 3)) {
        if(strlen(request.code) > 3) {
            cout << "MST: not found!" << endl;
        }
        else {
            int check = 0;
            int Time_ZERO = 0;
            int Num_Record = 0;
            L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
            while(pCurr != NULL) {
                int TimeCurrent = 0;
                Num_Record = pCurr->data.getSize();
                if(Num_Record > 1) {
                    check = 1;
                    //int TimeCurrent = 0;
                    L1Item<VRecord>* p = pCurr->data.getpHead();
                    L1Item<VRecord>* pp = p->pNext;
                    while(pp != NULL) {
                        double Sdd = distanceVR(p->data.y, p->data.x, pp->data.y, pp->data.x);
                        if(Sdd == ZERO) {
                        //if(Sdd <= STOP) {
                            TimeCurrent = TimeCurrent + difftime(pp->data.timestamp, p->data.timestamp);
                        }
                        else {
                            TimeCurrent = 0;
                        }
                        if(Time_ZERO < TimeCurrent) {
                            Time_ZERO = TimeCurrent;
                        }
                        p = pp;
                        pp = pp->pNext;
                    }
                }
                pCurr = pCurr->pNext;
            }
            if(check == 0) {
                cout << "MST : non stop!" << endl;
            }
            else {
                cout << "MST: " << Time_ZERO << "s" << endl;
            }
        }
    }

    else if (!strncmp(request.code, "CNR", 3)) {
        //cout << request.code << ": " << recList.getSize() << endl;
        if(strlen(request.code) > 3) {
            cout << "CNR: not found!" << endl;
        }
        else {
            int Num_Record = 0;
            L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
            while(pCurr != NULL) {
                Num_Record = Num_Record + pCurr->data.getSize();
                pCurr = pCurr->pNext;
            }
            cout << request.code << ": " << Num_Record << endl;
        }
    }

    else if (!strncmp(request.code, "MRV", 3)) {
        if(strlen(request.code) > 3) {
            cout << "MRV: not found!" << endl;
        }
        else {
            int Num_Record = 0;
            L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
            L1Item<VRecord>* p = NULL;
            while(pCurr != NULL) {
                int Num_Record_ID = 0;
                Num_Record_ID = pCurr->data.getSize();
                if(Num_Record < Num_Record_ID) {
                    Num_Record = Num_Record_ID;
                    p = pCurr->data.getpHead();
                }
                pCurr = pCurr->pNext;
            }
            cout << "MRV: " << p->data.id << endl;
        }
    }

    else if (!strncmp(request.code, "LRV", 3)) {
        if(strlen(request.code) > 3) {
            cout << "LRV: not found!" << endl;
        }
        else {
            L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
            //L1Item<L1List<VRecord>>* pTemp = pCurr;
            int Num_Record = pCurr->data.getSize();
            L1Item<VRecord>* p = pCurr->data.getpHead();
            pCurr = pCurr->pNext;
            while(pCurr != NULL) {
                int Num_Record_ID = pCurr->data.getSize();
                if(Num_Record > Num_Record_ID) {
                    Num_Record = Num_Record_ID;
                    p = pCurr->data.getpHead();
                }
                pCurr = pCurr->pNext;
            }
            cout << "LRV: " << p->data.id << endl;
        }
    }

    else if (!strncmp(request.code, "MTV", 3)) {
        if(strlen(request.code) > 3) {
            cout << "MTV: not found!" << endl;
        }
        else {
            int Time_Move_MAX = 0;
            L1Item<L1List<VRecord>>* pTemp = NULL;
            L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
            while(pCurr != NULL) {
                int Num_Record_ID = pCurr->data.getSize();
                if(Num_Record_ID > 1) {
                    int Time_Move_ID = 0;
                    L1Item<VRecord>* p = pCurr->data.getpHead();
                    L1Item<VRecord>* pp = p->pNext;
                    while(pp != NULL) {
                        if(distanceVR(p->data.y, p->data.x, pp->data.y, pp->data.x) > STOP) {
                        //if(p->data.y == pp->data.y && p->data.x == pp->data.x) {
                            Time_Move_ID = Time_Move_ID + difftime(pp->data.timestamp, p->data.timestamp);
                        }
                        p = pp;
                        pp = pp->pNext;
                    }
                    if(Time_Move_MAX < Time_Move_ID) {
                        Time_Move_MAX = Time_Move_ID;
                        pTemp = pCurr;
                    }
                }
                pCurr = pCurr->pNext;
            }
            cout << "MTV: " << pTemp->data.getpHead()->data.id << endl;
        }
    }

    else if (!strncmp(request.code, "MVV", 3)) {
        if(strlen(request.code) > 3) {
            cout << "MVV: not found!" << endl;
        }
        else {
            double MAX_V = ZERO;
            L1Item<L1List<VRecord>>* pTemp = NULL;
            L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
            while(pCurr != NULL) {
                int Num_Record_ID = pCurr->data.getSize();
                if(Num_Record_ID > 1) {
                    double S_Move = ZERO;
                    int Time_Move_ID = 0;
                    L1Item<VRecord>* p = pCurr->data.getpHead();
                    L1Item<VRecord>* pp = p->pNext;
                    while(pp != NULL) {
                        if(distanceVR(p->data.y, p->data.x, pp->data.y, pp->data.x) > STOP) {
                            S_Move = S_Move + distanceVR(p->data.y, p->data.x, pp->data.y, pp->data.x);
                            Time_Move_ID = Time_Move_ID + difftime(pp->data.timestamp, p->data.timestamp);
                        }
                        p = pp;
                        pp = pp->pNext;
                    }
                    if(Time_Move_ID != 0) {
                        double V_Move_ID = S_Move / Time_Move_ID;
                        if(MAX_V < V_Move_ID) {
                            MAX_V = V_Move_ID;
                            pTemp = pCurr;
                        }
                    }
                }
                pCurr = pCurr->pNext;
            }
            cout << "MVV: " << pTemp->data.getpHead()->data.id << endl;
        }
    }

    else if (!strncmp(request.code, "CNS", 3)){
        if(strlen(request.code) > 3) {
            cout << "CNS: not found!" << endl;
        }
        else {
            int Num = 0;
            L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
            while(pCurr != NULL) {
                int Check = 0;
                if(pCurr->data.getSize() > 1) {
                    L1Item<VRecord>* p = pCurr->data.getpHead();
                    L1Item<VRecord>* pp = p->pNext;
                    while(pp != NULL) {
                        if(distanceVR(p->data.y,p->data.x, pp->data.y, pp->data.x) <= STOP) {
                            Check = 1;
                            break;
                        }
                        p = pp;
                        pp = pp->pNext;
                    }
                    if(Check == 0) {
                        Num = Num + 1;
                    }
                }
                else {
                    Num = Num + 1;
                }
                pCurr = pCurr->pNext;
            }
            cout << request.code << ": " << Num << endl;
        }
    }

    else if (!strncmp(request.code, "CAS", 3)){
        if(strlen(request.code) > 3) {
            cout << "CAS: not found!" << endl;
        }
        else {
            L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
            double S_medium = ZERO;
            int Num_Record = 0;
            while(pCurr != NULL) {
                int Num_Record_ID = pCurr->data.getSize();
                if(Num_Record_ID > 1){
                    double S = ZERO;
                    L1Item<VRecord>* p = pCurr->data.getpHead();
                    L1Item<VRecord>* pp = p->pNext;
                    while(pp != NULL) {
                        S = S + distanceVR(p->data.y, p->data.x, pp->data.y, pp->data.x);
                        p = pp;
                        pp = pp->pNext;
                    }
                    S_medium = S_medium + S;
                    Num_Record = Num_Record + (Num_Record_ID - 1);
                }

                pCurr = pCurr->pNext;
            }
            S_medium = S_medium / Num_Record * 1000;
            cout << "CAS: " << S_medium << " meter" << endl;
        }
    }

    else if (!strncmp(request.code, "LPV", 3)) {
        if(strlen(request.code) > 3) {
            cout << "LPV: not found!" << endl;
        }
        else {
            L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
            L1Item<L1List<VRecord>>* pTemp = NULL;
            double S_MAX = ZERO;
            //pCurr = pCurr->pNext;
            while(pCurr != NULL) {
                int Num_Record_ID = pCurr->data.getSize();
                if(Num_Record_ID > 1) {
                    double S_ID = ZERO;
                    L1Item<VRecord>* p = pCurr->data.getpHead();
                    L1Item<VRecord>* pp = p->pNext;
                    while(pp != NULL) {
                        if(distanceVR(p->data.y, p->data.x, pp->data.y, pp->data.x) > STOP) {
                            S_ID = S_ID + distanceVR(p->data.y, p->data.x, pp->data.y, pp->data.x);
                        }
                        p = pp;
                        pp = pp->pNext;
                    }
                    if(S_MAX < S_ID) {
                        S_MAX = S_ID;
                        pTemp = pCurr;
                    }
                }
                pCurr = pCurr->pNext;
            }
            cout << "LPV: " << pTemp->data.getpHead()->data.id << endl;
        }
    }

    else if (!strncmp(request.code, "SPV", 3)) {
        if(strlen(request.code) > 3) {
            cout << "SPV: not found!" << endl;
        }
        else {
            L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
            L1Item<L1List<VRecord>>* pTemp = NULL;
            double S_MIN = START;
            //pCurr = pCurr->pNext;
            while(pCurr != NULL) {
                int Num_Record_ID = pCurr->data.getSize();
                if(Num_Record_ID > 1) {
                    double S_ID = ZERO;
                    L1Item<VRecord>* p = pCurr->data.getpHead();
                    L1Item<VRecord>* pp = p->pNext;
                    while(pp != NULL) {
                        if(distanceVR(p->data.y, p->data.x, pp->data.y, pp->data.x) > STOP) {
                            S_ID = S_ID + distanceVR(p->data.y, p->data.x, pp->data.y, pp->data.x);
                        }
                        p = pp;
                        pp = pp->pNext;
                    }
                    if(S_MIN > S_ID || S_MIN == START) {
                        S_MIN = S_ID;
                        pTemp = pCurr;
                    }
                }
                pCurr = pCurr->pNext;
            }
            cout << "SPV: " << pTemp->data.getpHead()->data.id << endl;
        }
    }

    else if (!strncmp(request.code, "RVR", 3)) {
        char* ID = getRequestID(request);
        
        L1Item<L1List<VRecord>>* pCurr = DoubleLinkedList.getpHead();
        L1Item<L1List<VRecord>>* pPrev = NULL;
        int flag = 0;
        int Check = 0;
        while(pCurr != NULL) {
            if(strcmp(pCurr->data.getpHead()->data.id, ID) == 0) {
                if(flag == 0) {
                    pCurr = pCurr->pNext;
                    DoubleLinkedList.removeHead();
                }
                else {
                    pPrev->pNext = pCurr->pNext;
                    pCurr->pNext = NULL;
                    DoubleLinkedList.decreaseSize();
                    delete pCurr;
                }
                Check = 1;
                cout << "RVR" << ID << ": success!" << endl;
                break;
            }
            else {
                pPrev = pCurr;
                pCurr = pCurr->pNext;
                flag++;
            }
        }
        if(Check == 0) {
            cout << "RVR" << ID << ": not found!" << endl;
        }
        /*
        else {
            L1Item<VRecord>* pDEL = recList.getpHead();
            L1Item<VRecord>* prev = NULL;
            int flag = 0;
            while(pDEL != NULL) {
                if(strcmp(pDEL->data.id, ID) == 0) {
                    if(flag == 0) {
                        pDEL = pDEL->pNext;
                        recList.removeHead();
                    }
                    else {
                        prev->pNext = pDEL->pNext;
                        L1Item<VRecord>* pT = pDEL;
                        pDEL = pDEL->pNext;
                        recList.decreaseSize();
                        delete pDEL;
                    }
                }
                else {
                    prev = pDEL;
                    pDEL = pDEL->pNext;
                    flag++;
                }
            }
        }
        */
    }

    else {
        return false;
    }
    
    return true;
}
