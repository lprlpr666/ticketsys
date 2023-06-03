//
// Created by 陆鹏睿 on 2023/5/21.
//

#ifndef UNTITLED97_INSTRUCTIONS_H
#define UNTITLED97_INSTRUCTIONS_H
bool ifffirstuser=0;
bool ifout=0;

void processing(string &s, user &usership, ticket_base &ticketbase, traindatabase &bpt_train);
bpt< myhashtrainforid ,int>trainrelease;
bpt<station, myhashtrainforid >station_to_trainid;
bpt<pair< myhashtrainforid ,int>,all_seat>bpt_seaat;
bpt<pair< myhashtrainforid ,int>,orderfinish>bpt_order;
bpt<username,orderfinish>bpt_history_order;
void start(){
    user usership;
    ticket_base ticketbase;
    traindatabase bpt_train;
    //test
    //
//     freopen("1.in", "r", stdin);
//     freopen("1.out", "w", stdout);
    int strp=1;
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    bpt_order.setfile("orderfinish.db");
    bpt_seaat.setfile("seat.db");
    station_to_trainid.setfile("station_to_train.db");
    bpt_history_order.setfile("history.db");
        std::string inlinestring;
        while(getline(std::cin, inlinestring)) {
            strp++;
            processing(inlinestring,usership,ticketbase,bpt_train);
            if(ifout) {
                ifout = 0;
                cout << "bye" << endl;
                return;
            }
        }
};
class pq{
public:
    char  trainidd[33];
    int cmp;
    Time leave,arrve;
    int price;
    int seats;
    pq(char * trr,int cmpp,Time leave1,Time arrve1,int price1,int seats1):
            cmp(cmpp),price(price1),seats(seats1),leave(leave1),arrve(arrve1){
        strcpy(trainidd,trr);
    }
    pq(const pq&other):cmp(other.cmp),leave(other.leave),arrve(other.arrve),
                       price(other.price),seats(other.seats){
        strcpy(trainidd,other.trainidd);
    }
    friend  bool operator<(const pq&x1,const pq&x2){
        if(x1.cmp==x2.cmp){
            return strcmp(x1.trainidd,x2.trainidd)>0;
        }
        return x1.cmp>x2.cmp;
    }
};

void processing(string &s, user &usership, ticket_base &ticketbase, traindatabase &bpt_train) {
//    if(usership.loginmembers.contains("Ethan")){
//        cout<<"ifout";
//    }
    Tokenscanner mytoken;
    mytoken.setInput(s);
    string tmp;
    string shijianchuo;
    shijianchuo = mytoken.nextToken();
    cout << shijianchuo << " ";
    tmp = mytoken.nextToken();
    if (tmp == "add_user") {
        if (usership.bppt.empty()) {
            ifffirstuser = 1;
            char cur_username[21];
            char username[21];
            char password[31];
            char realname[20];
            char mailaddress[31];
            int privilige;
            while ((tmp = mytoken.nextToken()) != "") {
                if (tmp == "-u") {
                    tmp = mytoken.nextToken();
                    std::strcpy(username, tmp.c_str());
                } else if (tmp == "-p") {
                    tmp = mytoken.nextToken();
                    strcpy(password, tmp.c_str());
                } else if (tmp == "-g") {
                    tmp = mytoken.nextToken();
                    privilige = 10;
                } else if (tmp == "-n") {
                    tmp = mytoken.nextToken();
                    strcpy(realname, tmp.c_str());
                } else if (tmp == "-m") {
                    tmp = mytoken.nextToken();
                    strcpy(mailaddress, tmp.c_str());
                } else if (tmp == "-c") {
                    tmp = mytoken.nextToken();
                }

            }
            usership.adduser(password, realname, mailaddress, username, 10);
            cout << 0 << "\n";
            return;
        } else {
            char cur_username[21];
            char username[21];
            char password[31];
            char realname[20];
            char mailaddress[31];
            account current;
            account newact;
            int privilige = -1;
            while ((tmp = mytoken.nextToken()) != "") {
                if (tmp == "-u") {
                    tmp = mytoken.nextToken();
                    std::strcpy(username, tmp.c_str());
                    if (!usership.finduser(username).empty()) {
                        cout << "-1\n";
                        return;
                    }
                } else if (tmp == "-p") {
                    tmp = mytoken.nextToken();
                    strcpy(password, tmp.c_str());
                } else if (tmp == "-g") {
                    tmp = mytoken.nextToken();
                    privilige = mytoken.check_num(tmp);
                } else if (tmp == "-n") {
                    tmp = mytoken.nextToken();
                    strcpy(realname, tmp.c_str());
                } else if (tmp == "-m") {
                    tmp = mytoken.nextToken();
                    strcpy(mailaddress, tmp.c_str());
                } else if (tmp == "-c") {
                    tmp = mytoken.nextToken();
                    strcpy(cur_username, tmp.c_str());

                    if(usership.finduser(cur_username).empty()){
                        cout << "-1\n";
                        return;
                    }
                    current = usership.finduser(cur_username)[0];
                    class username tmppp(cur_username);
                    if (usership.loginmembers.find(tmppp.hashing)==usership.loginmembers.end()) {
                        cout << "-1\n";
                        return;
                    }

                }
            }
            if (current.getprevillige() <= privilige) {
                cout << "-1\n";
                return;
            }
            usership.adduser(password, realname, mailaddress, username, privilige);
            cout << "0\n";
        }
    } else if (tmp == "login") {
        char cur_username[21];
        char username[21];
        char password[31];
        char realname[20];
        char mailaddress[31];
        while ((tmp = mytoken.nextToken()) != "") {
            if (tmp == "-u") {
                tmp = mytoken.nextToken();
                std::strcpy(username, tmp.c_str());
            } else if (tmp == "-p") {
                tmp = mytoken.nextToken();
                strcpy(password, tmp.c_str());
            }
        }
        if (usership.login(username, password) == -1) {
            cout << "-1\n";
            return;
        } else {
            cout << "0\n";
            return;
        }
        return;
    } else if (tmp == "logout") {
        tmp = mytoken.nextToken();
        if (tmp == "-u") {
            tmp = mytoken.nextToken();
            char tmpp[22];
            strcpy(tmpp, tmp.c_str());
            if (usership.logout(tmpp) == 1) {
                cout << "0\n";
            } else cout << "-1\n";
            return;
        }

    } else if (tmp == "query_profile") {
        char cur_username[21];
        char username[21];
        char password[31];
        char realname[20];
        char mailaddress[31];
        while ((tmp = mytoken.nextToken()) != "") {
            if (tmp == "-u") {
                tmp = mytoken.nextToken();
                std::strcpy(username, tmp.c_str());
            } else if (tmp == "-c") {
                tmp = mytoken.nextToken();
                strcpy(cur_username, tmp.c_str());
            }
        }
        sjtu::vector<account> veccur = usership.finduser(cur_username);
        if (veccur.empty()) {
            cout << "-1\n";
            return;
        }
        sjtu::vector<account> vectmp = usership.finduser(username);
        if (vectmp.empty()) {
            cout << "-1\n";
            return;
        }
        class username tmppp(cur_username);
        if (usership.loginmembers.find(tmppp.hashing)==usership.loginmembers.end()) {
            cout << "-1\n";
            return;
        }
        if (veccur[0].getprevillige() < vectmp[0].getprevillige()) {
            cout << "-1\n";
            return;
        }
        if (veccur[0].getprevillige() == vectmp[0].getprevillige() && strcmp(cur_username, username) != 0) {
            cout << "-1\n";
            return;
        }
        vectmp[0].qr();
        return;

    } else if (tmp == "modify_profile") {
        char cur_username[21];
        char username[21];
        char password[31] = "";
        char realname[20] = "";
        char mailaddress[31] = "";
        int privilige = -1;
        int pastpri;
        while ((tmp = mytoken.nextToken()) != "") {
            if (tmp == "-u") {
                tmp = mytoken.nextToken();
                std::strcpy(username, tmp.c_str());
            } else if (tmp == "-p") {
                tmp = mytoken.nextToken();
                strcpy(password, tmp.c_str());
            } else if (tmp == "-n") {
                tmp = mytoken.nextToken();
                strcpy(realname, tmp.c_str());
            } else if (tmp == "-m") {
                tmp = mytoken.nextToken();
                strcpy(mailaddress, tmp.c_str());
            } else if (tmp == "-c") {
                tmp = mytoken.nextToken();
                std::strcpy(cur_username, tmp.c_str());
            } else if (tmp == "-g") {
                tmp = mytoken.nextToken();
                privilige = mytoken.check_num(tmp);
            }

        }
        sjtu::vector<account> veccur = usership.finduser(cur_username);
        if (veccur.empty()) {
            cout << "-1\n";
            return;
        }
        sjtu::vector<account> vectmp = usership.finduser(username);
        if (vectmp.empty()) {
            cout << "-1\n";
            return;
        }
        class username tmppp(cur_username);
        if (usership.loginmembers.find(tmppp.hashing)==usership.loginmembers.end()) {
            cout << "-1\n";
            return;
        }

        if (veccur[0].getprevillige() < vectmp[0].getprevillige() || veccur[0].getprevillige() <= privilige) {
            cout << "-1\n";
            return;
        }
        if (veccur[0].getprevillige() == vectmp[0].getprevillige() && strcmp(cur_username, username) != 0) {
            cout << "-1\n";
            return;
        }
        usership.eraseuser(username, vectmp[0]);
        vectmp[0].modify(username, password, realname, mailaddress, privilige);
        usership.insert(username, vectmp[0]);
        vectmp[0].qr();
    } else if (tmp == "add_train") {
        //trainID：车次的唯一标识符，由字母开头，字母、数字和下划线组成的字符串，长度不超过 20。
        //
        //stationNum：车次经过的车站数量，一个不低于 2 且不超过 100 的整数。
        //
        //stations：车次经过的所有车站名，共 stationNum 项，每个站名由汉字组成，不超过 10 个汉字。
        //
        //seatNum：该车次的座位数，一个不超过 $10^5$ 的整数。
        //
        //prices：每两站之间的票价，共 (stationNum - 1) 项，第 i 项表示第 i 站到第 (i+1) 站的票价，为一个不超过 $10^5$ 的整数。
        //
        //startTime：列车每日的发车时间。
        //
        //时间格式为 hh:mm ，例如 23:51
        //travelTimes：每两站之间行车所用的时间，共 (stationNum - 1) 项。
        //
        //单位：分钟
        //每一项是一个不超过 $10^4$ 的整数
        //stopoverTimes：除始发站和终点站之外，列车在每一站停留的时间，共 (stationNum - 2) 项。
        //
        //单位：分钟
        //每一项为一个不超过 $10^4$ 的整数
        //saleDate：车次的售卖时间区间。
        //
        //由 2 项时间表示，每一项均为 2023 年 6 月至 8 月的某一日期
        //日期格式为 mm-dd，例如：06-01、08-31
        //type：列车类型，一个大写字母。

        char trainid[21];
        string tmptrainid;
        int stationNUm;
        string stations[100];
        int seatnum;
        int prices[100];
        int traveltime[100];
        daytime starttime;
        int stopoverTimes[100];
        monthtime saledatamonth1;
        monthtime saledatamonth2;
        char type;

        while ((tmp = mytoken.nextToken()) != "") {

            if (tmp == "-i") {
                //trainID
                tmp = mytoken.nextToken();
                strcpy(trainid, tmp.c_str());
                if (!bpt_train.bpt_train.find( myhashtrainforid (trainid)).empty()) {
                    cout << "-1\n";
                    return;
                }
            } else if (tmp == "-n") {
                //<stationNum>
                tmp = mytoken.nextToken();
                stationNUm = mytoken.check_num(tmp);
            } else if (tmp == "-m") {
                //<seatNum>
                tmp = mytoken.nextToken();
                seatnum = mytoken.check_num(tmp);
            } else if (tmp == "-s") {
                //<stations>
                tmp = mytoken.nextToken();
                int len = tmp.size();
                char stationname[31];
                int p = 0;
                int num = 0;
                for (int i = 0; i < len; i++) {
                    if (tmp[i] != '|') {
                        stationname[p] = tmp[i];
                        p++;
                    } else {
                        stationname[p] = '\0';
                        p = 0;
                        stations[num++] = stationname;
                    }
                }
                stationname[p] = '\0';
                stations[num] = stationname;
            } else if (tmp == "-p") {
                //<prices>
                int tmppricrs = 0;
                tmp = mytoken.nextToken();
                int len = tmp.size();
                int p = 0;
                int num = 0;
                for (int i = 0; i < len; i++) {
                    if (tmp[i] != '|') {
                        tmppricrs = 10 * tmppricrs + tmp[i] - '0';
                        p++;
                    } else {
                        prices[num++] = tmppricrs;
                        p = 0;
                        tmppricrs = 0;
                    }
                }
                prices[num++] = tmppricrs;
            } else if (tmp == "-x") {
                //<startTime>
                int tmpstart[2];
                int tmpstarttimr = 0;
                tmp = mytoken.nextToken();
                int len = tmp.size();
                int p = 0;
                for (int i = 0; i < len; i++) {
                    if (tmp[i] != ':') {
                        tmpstarttimr = 10 * tmpstarttimr + tmp[i] - '0';
                        p++;
                    } else {
                        tmpstart[0] = tmpstarttimr;
                        p = 0;
                        tmpstarttimr = 0;
                    }
                }
                tmpstart[1] = tmpstarttimr;
                starttime = {tmpstart[0], tmpstart[1]};
            } else if (tmp == "-t") {
                //<travelTimes>
                int tmptimes = 0;
                tmp = mytoken.nextToken();
                int len = tmp.size();
                int p = 0;
                int num = 0;
                for (int i = 0; i < len; i++) {
                    if (tmp[i] != '|') {
                        tmptimes = 10 * tmptimes + tmp[i] - '0';
                        p++;
                    } else {
                        traveltime[num++] = tmptimes;
                        p = 0;
                        tmptimes = 0;
                    }
                }
                traveltime[num++] = tmptimes;
            } else if (tmp == "-o") {
                //<stopoverTimes>
                int tmpstoptimes = 0;
                tmp = mytoken.nextToken();
                int len = tmp.size();
                int p = 0;
                int num = 0;
                if (tmp == "_") {
                    continue;
                }
                for (int i = 0; i < len; i++) {
                    if (tmp[i] != '|') {
                        tmpstoptimes = 10 * tmpstoptimes + tmp[i] - '0';
                        p++;
                    } else {
                        stopoverTimes[num++] = tmpstoptimes;
                        p = 0;
                        tmpstoptimes = 0;
                    }
                }
                stopoverTimes[num++] = tmpstoptimes;
            } else if (tmp == "-d") {
                //<saleDate>
                int tmpsaledata = 0;
                tmp = mytoken.nextToken();
                int len = tmp.size();
                int p = 0;
                int array[4];
                int arrayp = 0;
                for (int i = 0; i < len; i++) {
                    if (tmp[i] != '-' && tmp[i] != '|') {
                        tmpsaledata = 10 * tmpsaledata + tmp[i] - '0';
                        p++;
                    } else {
                        array[arrayp] = tmpsaledata;
                        arrayp++;
                        p = 0;
                        tmpsaledata = 0;
                    }
                }
                array[arrayp] = tmpsaledata;
                saledatamonth1 = {array[0], array[1]};
                saledatamonth2 = {array[2], array[3]};
            } else if (tmp == "-y") {
                //<type>
                tmp = mytoken.nextToken();
                type = tmp[0];
            }

        }
        traintrain tmptrrr(trainid,
                           stationNUm,
                           stations,
                           seatnum,
                           prices,
                           starttime,
                           traveltime,
                           stopoverTimes,
                           saledatamonth1,
                           saledatamonth2, type, 0);
        bpt_train.add_train(trainid, tmptrrr);
//        for(int i=0;i<=93;i++)
////        bpt_seaat.insert({trainid,i}, seatnum);
        cout << "0\n";
//        tmp="";
    } else if (tmp == "delete_train") {
        tmp = mytoken.nextToken();
        if (tmp == "-i") {
            tmp = mytoken.nextToken();
            char trainidd[21];
            strcpy(trainidd, tmp.c_str());
            sjtu::vector<int> fingg = bpt_train.bpt_train.find(trainidd);
            if (fingg.empty()) {
                cout << "-1\n";
                return;
            }
            traintrain tmptr = bpt_train.traindb.find(fingg[0]);
            if (tmptr.release == 1) {
                cout << "-1\n";
                return;
            }
            bpt_train.bpt_train.erase(trainidd, fingg[0]);
//            all_seat tmp = bpt_seaat.find(trainidd)[0];
//            bpt_seaat.erase(trainidd, tmp);
            bpt_train.traindb.erase(fingg[0]);
//            bpt_train.station_base.erase();
//            for(int i=0;i<fingg[0].stationNUm;i++){
//                station_to_trainid.erase(fingg[0].stations[i],trainidd);
//            }
            cout << "0\n";
            return;
        }
    } else if (tmp == "release_train") {
        tmp = mytoken.nextToken();
        tmp = mytoken.nextToken();
        char trainidd[21];
        strcpy(trainidd, tmp.c_str());
        sjtu::vector<int> fingg = bpt_train.bpt_train.find(trainidd);
        if (fingg.empty()) {
            cout << "-1\n";
            return;
        }
        traintrain tmptr = bpt_train.traindb.find(fingg[0]);
        if (tmptr.release == 0) {
            cout << "0\n";
            tmptr.release = 1;
            bpt_train.bpt_train.erase(trainidd, fingg[0]);
            bpt_train.traindb.erase(fingg[0]);
            bpt_train.bpt_train.insert(trainidd, bpt_train.traindb.insert(tmptr));
            for (int i = 0; i < tmptr.stationNUm; i++) {
                bpt_train.station_base.insert(station(tmptr.stations[i]), {trainidd, i});
            }
            Time end(tmptr.saledatamonth2, {0, 0});
            Time start(tmptr.saledatamonth1, {0, 0});
            int days_to = end.days_to(start);
            for (int i = 0; i <= days_to; i++) {
                ticketbase.ticket_base_.insert({trainidd, i}, ticketbase.ticket_database.insert(
                        {tmptr.seatnum, tmptr.stationNUm}));
            }
            return;
        }

        cout << "-1\n";
        return;
    } else if (tmp == "query_train") {
        monthtime starttime;
        char trainidd[21];
        traintrain tmptrain;
        while ((tmp = mytoken.nextToken()) != "") {
            if (tmp == "-i") {
                tmp = mytoken.nextToken();
                strcpy(trainidd, tmp.c_str());
                sjtu::vector<int> fingg = bpt_train.bpt_train.find(trainidd);
                if (fingg.empty()) {
                    cout << "-1\n";
                    return;
                }
                tmptrain = bpt_train.traindb.find(fingg[0]);
            } else {
                int tmpstart[2];
                int tmpstarttimr = 0;
                tmp = mytoken.nextToken();
                int len = tmp.size();
                int p = 0;
                int sump = 0;
                for (int i = 0; i < len; i++) {
                    if (tmp[i] != '-') {
                        tmpstarttimr = 10 * tmpstarttimr + tmp[i] - '0';
                        p++;
                    } else {
                        tmpstart[sump++] = tmpstarttimr;
                        p = 0;
                        tmpstarttimr = 0;
                    }
                }
                tmpstart[1] = tmpstarttimr;
                starttime = {tmpstart[0], tmpstart[1]};
            }
        }
        if (tmptrain.release) {
            Time nowtime(starttime, tmptrain.starttime);
            Time ini(tmptrain.saledatamonth1, tmptrain.starttime);
            Time last(tmptrain.saledatamonth2, tmptrain.starttime);
            int days_to = nowtime.days_to(ini);
            if (starttime < tmptrain.saledatamonth1 || starttime > tmptrain.saledatamonth2) {
                cout << "-1\n";
                return;
            }
            int seeaatt = ticketbase.ticket_base_.find({trainidd, days_to})[0];
            everydayticketsys seat = ticketbase.ticket_database.find(seeaatt);
            cout << tmptrain.trainid << ' ' << tmptrain.type << '\n' << tmptrain.stations[0] << " xx-xx xx:xx -> "
                 << nowtime.toString() << " 0 " << seat.everydayticket[0] << '\n';
            for (int i = 1; i < tmptrain.stationNUm - 1; i++) {
                nowtime = nowtime + tmptrain.traveltime[i - 1];
                cout << tmptrain.stations[i] << ' ' << nowtime.toString() << " -> ";
                nowtime = nowtime + tmptrain.stopoverTimes[i - 1];
                cout << nowtime.toString() << ' ' << tmptrain.sumprices[i - 1] << ' ' << seat.everydayticket[i] << '\n';
            }
            nowtime = nowtime + tmptrain.traveltime[tmptrain.stationNUm - 2];
            cout << tmptrain.stations[tmptrain.stationNUm - 1] << ' ' << nowtime.toString() << " -> xx-xx xx:xx "
                 << tmptrain.sumprices[tmptrain.stationNUm - 2] << " x\n";
        } else {
            Time nowtime(starttime, tmptrain.starttime);
            Time ini(tmptrain.saledatamonth1, tmptrain.starttime);
            Time last(tmptrain.saledatamonth2, tmptrain.starttime);
            int days_to = nowtime.days_to(ini);
            if (starttime < tmptrain.saledatamonth1 || starttime > tmptrain.saledatamonth2) {
                cout << "-1\n";
                return;
            }
            cout << tmptrain.trainid << ' ' << tmptrain.type << '\n' << tmptrain.stations[0] << " xx-xx xx:xx -> "
                 << nowtime.toString() << " 0 " << tmptrain.seatnum << '\n';
            for (int i = 1; i < tmptrain.stationNUm - 1; i++) {
                nowtime = nowtime + tmptrain.traveltime[i - 1];
                cout << tmptrain.stations[i] << ' ' << nowtime.toString() << " -> ";
                nowtime = nowtime + tmptrain.stopoverTimes[i - 1];
                cout << nowtime.toString() << ' ' << tmptrain.sumprices[i - 1] << ' ' << tmptrain.seatnum << '\n';
            }
            nowtime = nowtime + tmptrain.traveltime[tmptrain.stationNUm - 2];
            cout << tmptrain.stations[tmptrain.stationNUm - 1] << ' ' << nowtime.toString() << " -> xx-xx xx:xx "
                 << tmptrain.sumprices[tmptrain.stationNUm - 2] << " x\n";
        }

//        sjtu::monthtime starttime;char trainidd[21];
//        traintrain tmptrain;
//        tmp=mytoken.nextToken();
//        if(tmp=="-i"){
//            tmp=mytoken.nextToken();
//            strcpy(trainidd,tmp.c_str());
//            if(bpt_train.bpt_train.find(trainidd).empty()){
//                cout<<"-1\n";
//                return;
//            }
//            if(trainrelease.find(trainidd).empty()){
//                cout<<"-1\n";
//                return;
//            }
//
//        }
//        else{
//            int tmpstart[2];
//            tmp = mytoken.nextToken();
//            int tmpstarttimr;
//            tmp = mytoken.nextToken();
//            int len=tmp.size();
//            int p=0;
//            for(int i=0;i<len;i++){
//                if(tmp[i]!=':'){
//                    tmpstarttimr=10*tmpstarttimr+tmp[i]-'0';
//                    p++;
//                }
//                else{
//                    tmpstart[0]=tmpstarttimr;
//                    p=0;
//                }
//            }
//            tmpstart[1]=tmpstarttimr;
//            starttime={tmpstart[0],tmpstart[1]};
//        }
//
//        tmptrain=bpt_train.bpt_train.find(trainidd)[0];cout<<tmptrain.trainid<<" "<<tmptrain.type<<'\n';
//        sjtu::vector<station>tmpstation(tmptrain.stations);
//        sjtu::vector<int>newstop(tmptrain.stopoverTimes);
//        sjtu::vector<int>travletime(tmptrain.traveltime);
//        sjtu::vector<int>prices(tmptrain.prices);
//        auto iterstation=tmpstation.begin();
//        auto iternewstop=newstop.begin();
//        auto itertravletime=travletime.begin();
//        auto iterprices=prices.begin();
//        Time nowtime={starttime,tmptrain.starttime};
//        cout<<(*iterstation).name<<" xx-xx xx:xx -> "<<nowtime.toString()<<' '<<*iterprices<<' '<<(waaitingfor seat)<<'\n';
//        for(int i=1;i<=tmptrain.stationNUm-2;i++){
//            iterstation++;
//            iterprices++;
//            nowtime=nowtime+(*itertravletime);
//            cout<<(*iterstation).name<<' '<<nowtime.toString()<<" -> ";
//            nowtime=nowtime+(*iternewstop);
//            cout<<nowtime.toString()<<' '<<*iterprices<<' '<<(sseeaaatt)<<'\n';
//            itertravletime++;iternewstop++;
//        }
//        iterstation++;
//        iterprices++;
//        nowtime=nowtime+(*itertravletime);
//        cout<<(*iterstation).name<<' '<<nowtime.toString()<<" -> xx-xx xx:xx ";
//        cout<<*iterprices<<" x\n";
    } else if (tmp == "query_ticket") {
        char trainid[21];
        char username[21];
        monthtime date;
        char from[33], to[33];
        int p_p = 1;
        //1   time
        //2   cost
        while ((tmp = mytoken.nextToken()) != "") {
            if (tmp == "-s") {
                tmp = mytoken.nextToken();
                strcpy(from, tmp.c_str());

            } else if (tmp == "-t") {
                tmp = mytoken.nextToken();
                strcpy(to, tmp.c_str());
            } else if (tmp == "-d") {
                int tmpdata = 0;
                tmp = mytoken.nextToken();
                int len = tmp.size();
                int p = 0;
                int array[4];
                int arrayp = 0;
                for (int i = 0; i < len; i++) {
                    if (tmp[i] != '-' && tmp[i] != ':') {
                        tmpdata = 10 * tmpdata + tmp[i] - '0';
                        p++;
                    } else {
                        array[arrayp] = tmpdata;
                        arrayp++;
                        p = 0;
                        tmpdata = 0;
                    }
                }
                array[arrayp] = tmpdata;
                date = {array[0], array[1]};
            } else if (tmp == "-p") {
                tmp = mytoken.nextToken();
                if (tmp == "cost")p_p = 2;
            }
        }
        sjtu::priority_queue<pq> prioq;
        sjtu::vector<pairwithtrainandplace> pairingfrom = bpt_train.station_base.find(from);
        sjtu::vector<pairwithtrainandplace> pairingto = bpt_train.station_base.find(to);
        auto iterfrom = pairingfrom.begin(), iterto = pairingto.begin();
        int shit = pairingfrom.size();
        int shit2 = pairingto.size();
        while (iterfrom != pairingfrom.end() && iterto != pairingto.end()) {
            if (strcmp((*iterfrom).ID, (*iterto).ID) < 0) {
                iterfrom++;
                continue;
            }
            if (strcmp((*iterfrom).ID, (*iterto).ID) > 0) {
                iterto++;
                continue;
            }
            if ((*iterfrom).pos >= (*iterto).pos) {
                iterfrom++;
                iterto++;
                continue;
            }
            int fingg = bpt_train.bpt_train.find((*iterfrom).ID)[0];
            traintrain tmptr = bpt_train.traindb.find(fingg);
            if (tmptr.release == 0) {
                iterfrom++;
                iterto++;
                continue;
            }
            Time firsttrian(tmptr.saledatamonth1, tmptr.starttime);
            Time lasttraih(tmptr.saledatamonth2, tmptr.starttime);
            int totaltime = 0;
            int sumprice = 0;
            if ((*iterfrom).pos != 0) {
                lasttraih = lasttraih + tmptr.sumtime[(*iterfrom).pos - 1];
                sumprice = tmptr.sumprices[(*iterto).pos - 1] - tmptr.sumprices[(*iterfrom).pos - 1];
                firsttrian = firsttrian + tmptr.sumtime[(*iterfrom).pos - 1];
                totaltime = tmptr.sumtime[(*iterto).pos - 1] - tmptr.sumtime[(*iterfrom).pos - 1];
            } else {
                sumprice = tmptr.sumprices[(*iterto).pos - 1];
                totaltime = tmptr.sumtime[(*iterto).pos - 1];
            }

            Time now(date, {firsttrian.hour_, firsttrian.minute_});
            Time arrve;
            if (((*iterto).pos + 1) != tmptr.stationNUm) {
                arrve = now + totaltime - tmptr.stopoverTimes[(*iterto).pos - 1];
                totaltime = totaltime - tmptr.stopoverTimes[(*iterto).pos - 1];
            } else {
                arrve = now + totaltime;
            }
            if (date > monthtime{lasttraih.month_, lasttraih.day_}) {
                iterfrom++;
                iterto++;
                continue;
            }
            if (date < monthtime{firsttrian.month_, firsttrian.day_}) {
                iterfrom++;
                iterto++;
                continue;
            }
            int day_to = now.days_to(firsttrian);
            ::strcpy(trainid, (*iterfrom).ID);
            int fingseat = ticketbase.ticket_base_.find({trainid, day_to})[0];
            everydayticketsys seat = ticketbase.ticket_database.find(fingseat);
            int seatnum = 239913123;
            for (int i = (*iterfrom).pos; i < (*iterto).pos; i++) {
                seatnum = min(seatnum, seat.everydayticket[i]);
            }

            if (p_p == 1) {
                pq e(trainid, totaltime, now, arrve, sumprice, seatnum);
                prioq.push(e);
            } else {
                pq e(trainid, sumprice, now, arrve, sumprice, seatnum);
                prioq.push(e);
            }
            iterfrom++;
            iterto++;
        }
        cout << prioq.size() << '\n';
        while (!prioq.empty()) {
            pq tmppq(prioq.top());
            prioq.pop();
            string tmppp = tmppq.trainidd;
            cout << tmppp << ' ' << from << ' ' << tmppq.leave.toString() << " -> " << to << ' '
                 << tmppq.arrve.toString() << ' '
                 << tmppq.price << ' ' << tmppq.seats << '\n';
        }

        //        if (p_p == 1) {
//            //time
//            for(int j=0;j<trvec.size();j++){
////                traintrain tmptrain=bpt_train.bpt_train.find(trvec[j])[0];
//
//                    int frompos = -1, topos = -1;
//                    Time firsttrian(tmptrain.saledatamonth1, tmptrain.starttime);
//                    Time initail(firsttrian);
//                    for (int i = 0; i < tmptrain.stationNUm; i++) {
//                        if (frompos == -1) {
//                            if (tmptrain.stations[i] == from) {
//                                frompos = i;
//                            }
//                        }
//                        if (topos == -1) {
//                            if (tmptrain.stations[i] == to) {
//                                topos = i;
//                            }
//                        }
//                    }
//                    if (topos == -1 || frompos == -1 || frompos >= topos) {
//                        continue;
//                    }
//                    for (int i = 0; i < frompos; i++) {
//                        firsttrian = firsttrian + tmptrain.traveltime[i] + tmptrain.stopoverTimes[i];
//                    }
//                    Time hisleavetime(date, {firsttrian.getHour(), firsttrian.getMinute()});
//                    Time hisarrivetime(hisleavetime);
//                        int totaltime=0;int sum = 0;
//                        int seats=132139332;
//
//
//                    for (int i = frompos; i < topos - 1; i++) {
//
//                        sum += tmptrain.prices[i];
//                        hisarrivetime = hisarrivetime + tmptrain.traveltime[i] + tmptrain.stopoverTimes[i];
//                        totaltime  +=( tmptrain.traveltime[i] + tmptrain.stopoverTimes[i]);
//                    }
//                hisarrivetime = hisarrivetime + tmptrain.traveltime[topos - 1];
//                    totaltime+=tmptrain.traveltime[topos - 1];
//                sum += tmptrain.prices[topos-1];
//                    int days_to = hisleavetime.days_to(firsttrian);
//                if (days_to < 0) {
//                    continue;
//                }
//                //座位
//                auto fing=bpt_seaat.find({tmptrain.trainid, days_to})[0];
//                for(int i = frompos; i < topos; i++){
//                    seats=min(seats,fing.everydayseat[i]);
//                }
//
//                prioq.push(pq(tmptrain.trainid,totaltime,hisleavetime,hisarrivetime,sum,seats)            );
//            }
//            while(!prioq.empty()){
//                pq tmppq(prioq.top());
//                prioq.pop();
//                cout<<tmppq.trainidd<<' '<<from.name<<' '<<tmppq.leave.toString()<<" -> "<<tmppq.arrve.toString()<<' '
//                <<tmppq.price<<' '<<tmppq.seats<<'\n';
//            }
//        }
//        else{
//            //cost
//            for(int j=0;j<trvec.size();j++){
////                traintrain tmptrain=bpt_train.bpt_train.find(trvec[j])[0];
//
//                int frompos = -1, topos = -1;
//                Time firsttrian(tmptrain.saledatamonth1, tmptrain.starttime);
//                Time initail(firsttrian);
//                for (int i = 0; i < tmptrain.stationNUm; i++) {
//                    if (frompos == -1) {
//                        if (tmptrain.stations[i] == from) {
//                            frompos = i;
//                        }
//                    }
//                    if (topos == -1) {
//                        if (tmptrain.stations[i] == to) {
//                            topos = i;
//                        }
//                    }
//                }
//                if (topos == -1 || frompos == -1 || frompos >= topos) {
//                    continue;
//                }
//                for (int i = 0; i < frompos; i++) {
//                    firsttrian = firsttrian + tmptrain.traveltime[i] + tmptrain.stopoverTimes[i];
//                }
//                Time hisleavetime(date, {firsttrian.getHour(), firsttrian.getMinute()});
//                Time hisarrivetime(hisleavetime);
//                int totaltime=0;int sum = 0;
//                int seats=132139332;
//                for (int i = frompos; i < topos - 1; i++) {
//
//                    sum += tmptrain.prices[i];
//                    hisarrivetime = hisarrivetime + tmptrain.traveltime[i] + tmptrain.stopoverTimes[i];
//                    totaltime  +=( tmptrain.traveltime[i] + tmptrain.stopoverTimes[i]);
//                }
//                hisarrivetime = hisarrivetime + tmptrain.traveltime[topos - 1];
//                totaltime+=tmptrain.traveltime[topos - 1];
//                sum += tmptrain.prices[topos-1];
//                int days_to = hisleavetime.days_to(firsttrian);
//                if (days_to < 0) {
//                    continue;
//                }
//                //座位
//                auto fing=bpt_seaat.find({tmptrain.trainid,days_to})[0];
//                for(int i = frompos; i < topos; i++){
//                    seats=min(seats,fing.everydayseat[i]);
//                }
//
//                prioq.push(pq(tmptrain.trainid,sum,hisleavetime,hisarrivetime,sum,seats)            );
//            }
//            while(!prioq.empty()){
//                pq tmppq(prioq.top());
//                prioq.pop();
//                cout<<tmppq.trainidd<<' '<<from.name<<' '<<tmppq.leave.toString()<<" -> "<<tmppq.arrve.toString()<<' '
//                    <<tmppq.price<<' '<<tmppq.seats<<'\n';
//            }
//        }

    } else if (tmp == "query_transfer") {
        char trainid[21];
        char username[21];
        monthtime date;
        char from[33],
                to[33];
        int p_p = 0;
        int time_summm;
        int costsummm;
        string myout1, myout2;
        bool pan3 = 0;
        //0   time
        //1   cost
        while ((tmp = mytoken.nextToken()) != "") {
            if (tmp == "-s") {
                tmp = mytoken.nextToken();
                strcpy(from, tmp.c_str());
            } else if (tmp == "-t") {
                tmp = mytoken.nextToken();
                strcpy(to, tmp.c_str());
            } else if (tmp == "-d") {
                int tmpdata = 0;
                tmp = mytoken.nextToken();
                int len = tmp.size();
                int p = 0;
                int array[4];
                int arrayp = 0;
                for (int i = 0; i < len; i++) {
                    if (tmp[i] != '-' && tmp[i] != ':') {
                        tmpdata = 10 * tmpdata + tmp[i] - '0';
                        p++;
                    } else {
                        array[arrayp] = tmpdata;
                        arrayp++;
                        p = 0;
                        tmpdata = 0;
                    }
                }
                array[arrayp] = tmpdata;
                date = {array[0], array[1]};
            } else if (tmp == "-p") {
                tmp = mytoken.nextToken();
                if (tmp == "cost")p_p = 1;
            }
        }
        sjtu::vector<pairwithtrainandplace> position1 = bpt_train.station_base.find(from);
        sjtu::vector<pairwithtrainandplace> position3 = bpt_train.station_base.find(to);
        sjtu::vector<int> mytr;
        for (int i = 0; i < position1.size(); i++) {
            mytr.push_back(bpt_train.bpt_train.find(position1[i].ID)[0]);
        }
        for (int i = 0; i < position1.size(); i++) {
            traintrain tmptr = bpt_train.traindb.find(mytr[i]);
            if (tmptr.release == 0) {
                continue;
            }
            if (tmptr.stationNUm - 1 == position1[i].pos) {
                continue;
            }
            Time ini(tmptr.saledatamonth1, tmptr.starttime);
            int timefront;
            int moneyfront;
            if (position1[i].pos == 0) {
                timefront = 0;
                moneyfront = 0;
            } else {
                timefront = tmptr.sumtime[position1[i].pos - 1];
                moneyfront = tmptr.sumprices[position1[i].pos - 1];
            }
            ini = ini + timefront;
            Time hisleavetime(date, {ini.hour_, ini.minute_});
            Time Timefirst(tmptr.saledatamonth1, tmptr.starttime);
            Time Timelast(tmptr.saledatamonth2, tmptr.starttime);
            Timefirst = Timefirst + timefront;
            Timelast = Timelast + timefront;
            if (hisleavetime < Timefirst) {
                continue;
            }
            if (hisleavetime > Timelast) {
                continue;
            }
//            Time firtrtrr(tmptr.saledatamonth1, tmptr.starttime),
//                    lastrrrr(tmptr.saledatamonth2, tmptr.starttime);
            int days_to = hisleavetime.days_to(Timefirst);
            int time_summ;
            int cost_summ;
            std::string as1, as2;
            bool pan2 = 0;
            for (int j = position1[i].pos + 1; j < tmptr.stationNUm; j++) {
                int time_first = tmptr.sumtime[j - 1] - timefront - tmptr.stopoverTimes[j - 1];
                int cost_first = tmptr.sumprices[j - 1] - moneyfront;
                auto midtr = bpt_train.station_base.find(station(tmptr.stations[j]));//经过中转站的所有车
                auto iter1 = midtr.begin();
                auto iter2 = position3.begin();
                int time_s, cost_s;
                myhashtrainforid  id_;
                bool pan = 0;
                std::string ans;
                Time mid_time = hisleavetime + time_first;
                while (iter1 != midtr.end() && iter2 != position3.end()) {
                    if (strcmp((*iter1).ID, (*iter2).ID) < 0) {
                        iter1++;
                        continue;
                    }
                    if (strcmp((*iter1).ID, (*iter2).ID) > 0) {
                        iter2++;
                        continue;
                    }
                    if ((*iter1).pos >= (*iter2).pos) {
                        iter1++;
                        iter2++;
                        continue;
                    }
                    if (strcmp(position1[i].ID, (*iter1).ID) == 0) {
                        iter1++;
                        iter2++;
                        continue;
                    }
                    sjtu::vector<int> pos_2 = bpt_train.bpt_train.find(myhashtrainforid ((*iter1).ID));
                    traintrain tmptrs = bpt_train.traindb.find(pos_2[0]);
                    if (!tmptrs.release) {
                        iter1++;
                        iter2++;
                        continue;
                    }
                    Time midtimejudge(date, tmptrs.starttime);
                    int time1;
                    int monu1;
                    if ((*iter1).pos == 0) {
                        time1 = 0;
                        monu1 = 0;
                    } else {
                        time1 = tmptrs.sumtime[(*iter1).pos - 1];
                        monu1 = tmptrs.sumprices[(*iter1).pos - 1];
                    }
                    midtimejudge = midtimejudge + time1;
                    midtimejudge.month_=mid_time.month_;
                    midtimejudge.day_=mid_time.day_;
                    if (midtimejudge < mid_time)midtimejudge = midtimejudge + 24 * 60;//加上一天
                    Time starttrrr(tmptrs.saledatamonth1, tmptrs.starttime),
                            lasttrrr(tmptrs.saledatamonth2, tmptrs.starttime);
                    midtimejudge = midtimejudge - time1;
                    if (midtimejudge > lasttrrr) {
                        ++iter1;
                        iter2++;
                        continue;
                    }



//                    下面是错误的代码！！！！！！！！！！！！！！！！！！
//                    if (midtimejudge < starttrrr) {
//                        ++iter1;
//                        iter2++;
//                        continue;
//                    }int no = midtimejudge.days_to(Time(tmptrs.saledatamonth1));
//                    midtimejudge = midtimejudge + time1;
//                    int time_sum = tmptrs.sumtime[(*iter2).pos - 1] - time1
//                                   - tmptrs.stopoverTimes[(*iter2).pos - 1] + (midtimejudge - mid_time);
//                    int time_sum_ = time_sum - (midtimejudge - mid_time);
//                    int price_sum = tmptrs.sumprices[(*iter2).pos - 1] - monu1;
                    if (midtimejudge < starttrrr) {
                        midtimejudge = starttrrr;
                    }
                    int no = midtimejudge.days_to(Time(tmptrs.saledatamonth1));
                    midtimejudge = midtimejudge + time1;
                    int time_sum = tmptrs.sumtime[(*iter2).pos - 1] - time1
                                   - tmptrs.stopoverTimes[(*iter2).pos - 1] + (midtimejudge - mid_time);
                    int time_sum_ = time_sum - (midtimejudge - mid_time);
                    int price_sum = tmptrs.sumprices[(*iter2).pos - 1] - monu1;
//                    下面有问题
                    //if (pan) {
                    //                        if (p_p) {
                    //                            if (!(price_sum > cost_s || (price_sum == cost_s && time_sum < time_s))) {
                    //                                ++iter1;
                    //                                iter2++;
                    //                                continue;
                    //                            }
                    //                        } else {
                    //                            if (!(time_sum > time_s || (time_sum == time_s && price_sum < cost_s))) {
                    //                                ++iter1;
                    //                                iter2++;
                    //                                continue;
                    //                            }
                    //                        }
                    //                    }
                    //                    else {
                    //                        pan = 1;
                    //                    }
                    if (pan) {
                        if (p_p) {
                            if (!(price_sum < cost_s || (price_sum == cost_s && time_sum < time_s))) {
                                ++iter1;
                                iter2++;
                                continue;
                            }
                        } else {
                            if (!(time_sum < time_s || (time_sum == time_s && price_sum < cost_s))) {
                                ++iter1;
                                iter2++;
                                continue;
                            }
                        }
                    }
                    else {
                        pan = 1;
                    }
                    Time x2 = midtimejudge + time_sum_;
                    int seats = 111445144;
                    everydayticketsys left_temp(ticketbase.query(everydaytrain((*iter1).ID, no)));//no为第二辆车是第几班

                    for (int k = (*iter1).pos; k < (*iter2).pos; k++) {
                        seats = std::min(seats, left_temp.everydayticket[k]);
                    }

                    ans = std::string((*iter1).ID) + " " + std::string(tmptr.stations[j]) + " " +
                          midtimejudge.toString() + " -> " +
                          std::string(to) + " " + x2.toString() + " " + std::to_string(price_sum) + " " +
                          std::to_string(seats);
                    cost_s = price_sum;
                    time_s = time_sum;
                    ++iter1;
                    iter2++;
                }
                if (!pan)continue;
                int time_sums = time_first + time_s;
                int cost_sums = cost_first + cost_s;
//its wrong！！！
//                if(pan){
//                    int time_sums = time_first + time_s;
//                    int cost_sums = cost_first + cost_s;
//                }
                if (pan2) {
                    if (p_p) {
                        if (!(cost_sums < cost_summ || (cost_sums == cost_summ && time_sums < time_summ)))continue;
                    } else {
                        if (!(time_sums < time_summ || (time_sums == time_summ && cost_sums < cost_summ)))continue;
                    }
                }
                else {
                    pan2 = 1;
                }
                int seatsss = 11144514;
                everydayticketsys left_temp_(ticketbase.query(everydaytrain(position1[i].ID, days_to)));
                for (int k = position1[i].pos; k < j; k++) {
                    seatsss = std::min(seatsss, left_temp_.everydayticket[k]);
                }
                as1 = std::string(position1[i].ID) + " " + std::string(from) + " " + hisleavetime.toString() + " -> " +
                     std::string(tmptr.stations[j]) + " " + mid_time.toString() + " " + std::to_string(cost_first) +
                     " " + std::to_string(seatsss);
               as2 = ans;
                time_summ = time_sums;
                cost_summ = cost_sums;
            }
            if (!pan2)continue;
            //下面有问题
            // if (pan3) {
            //                if (p_p) {
            //                    if (!(cost_summ >costsummm || (cost_summ == costsummm && time_summ < time_summm)))continue;
            //                } else {
            //                    if (!(time_summ > time_summm || (time_summ == time_summm && cost_summ < costsummm)))continue;
            //                }
            //            } else {
            //                pan3 = 1;
            //            }
            //            myout1 = as1;
            //            myout2 = as2;
            //            time_summm = time_summ;
            //            costsummm = cost_summ;
            if (pan3) {
                if (p_p) {
                    if (!(cost_summ < costsummm || (cost_summ == costsummm && time_summ < time_summm)))continue;
                } else {
                    if (!(time_summ < time_summm || (time_summ == time_summm && cost_summ < costsummm)))continue;
                }
            } else {
                pan3 = 1;
            }
            myout1 = as1;
            myout2 = as2;
            time_summm = time_summ;
            costsummm = cost_summ;
        }
        if (!pan3) {
            cout << "0\n";
            return;
        }
        std::cout << myout1 << '\n' << myout2 << '\n';
        return;
    }
    else if (tmp == "buy_ticket") {
        char trainid[21];
        char username[21];
        traintrain tmptrain;
        monthtime date;
        int buynum;
        int ifq = 0;
        station from, to;
        while ((tmp = mytoken.nextToken()) != "") {
            if (tmp == "-i") {
                //trainID
                tmp = mytoken.nextToken();
                strcpy(trainid, tmp.c_str());
                sjtu::vector<int> tmptrr = bpt_train.bpt_train.find(trainid);

                if (tmptrr.empty()) {
                    cout << "-1\n";
                    return;
                }
                tmptrain = (bpt_train.traindb.find(tmptrr[0]));
                if (tmptrain.release == 0) {
                    cout << "-1\n";
                    return;
                }
            } else if (tmp == "-u") {
                //<username>
                tmp = mytoken.nextToken();
                strcpy(username, tmp.c_str());

                class username tmppp(username);
                if (usership.loginmembers.find(tmppp.hashing)==usership.loginmembers.end()) {
                    cout << "-1\n";
                    return;
                }
            } else if (tmp == "-d") {
                //<data>
                int tmpdata = 0;
                tmp = mytoken.nextToken();
                int len = tmp.size();
                int p = 0;
                int array[4];
                int arrayp = 0;
                for (int i = 0; i < len; i++) {
                    if (tmp[i] != '-' && tmp[i] != '|') {
                        tmpdata = 10 * tmpdata + tmp[i] - '0';
                        p++;
                    } else {
                        array[arrayp] = tmpdata;
                        arrayp++;
                        p = 0;
                        tmpdata = 0;
                    }
                }
                array[arrayp] = tmpdata;
                date = {array[0], array[1]};
            } else if (tmp == "-n") {
                //<number>
                tmp = mytoken.nextToken();
                buynum = mytoken.check_num(tmp);
            } else if (tmp == "-f") {
                //fronm
                tmp = mytoken.nextToken();
                from = tmp;
            } else if (tmp == "-t") {
                //to
                tmp = mytoken.nextToken();
                to = tmp;
            } else if (tmp == "-q") {
                //if queue?
                tmp = mytoken.nextToken();
                if (tmp[0] == 't')ifq = 1;
            }
        }
        //下面是更新作为
        //先找到那一个站的离开时间
        int frompos = -1, topos = -1;

        Time firsttrian(tmptrain.saledatamonth1, tmptrain.starttime);
        Time lasttrinsa(tmptrain.saledatamonth2, tmptrain.starttime);
        Time initail(firsttrian);
        for (int i = 0; i < tmptrain.stationNUm; i++) {
            if (frompos == -1) {
                if (tmptrain.stations[i] == from) {
                    frompos = i;
                }
            }
            if (topos == -1) {
                if (tmptrain.stations[i] == to) {
                    topos = i;
                }
            }
        }
        if (topos == -1 || frompos == -1 || frompos >= topos) {
            cout << "-1\n";
            return;
        }
        if (frompos != 0) {
            lasttrinsa = lasttrinsa + tmptrain.sumtime[frompos - 1];
            firsttrian = firsttrian + tmptrain.sumtime[frompos - 1];
        }
        Time hisleavetime(date, {firsttrian.hour_, firsttrian.minute_});
        Time hisarrivetime(hisleavetime);
        if (frompos == 0) {
            hisarrivetime = hisleavetime + tmptrain.sumtime[topos - 1];
        } else {
            hisarrivetime = hisleavetime - tmptrain.sumtime[frompos - 1] + tmptrain.sumtime[topos - 1];
        }
        if (buynum > tmptrain.seatnum) {
            cout << "-1\n";
            return;
        }
        if (topos != tmptrain.stationNUm - 1) {
            hisarrivetime = hisarrivetime - tmptrain.stopoverTimes[topos - 1];
        }
        int days_to = hisleavetime.days_to(firsttrian);
        if (date > monthtime{lasttrinsa.month_, lasttrinsa.day_}) {
            cout << "-1\n";
            return;
        }
        if (date <monthtime{firsttrian.month_, firsttrian.day_}) {
            cout << "-1\n";
            return;
        }
        int fingseat = ticketbase.ticket_base_.find({trainid, days_to})[0];
        everydayticketsys seat(ticketbase.ticket_database.find(fingseat));

        bool pan = 1;
        for (int i = frompos; i < topos; i++) {
            if (seat.everydayticket[i] < buynum) {
                pan = 0;
                break;
            }
        }
        if (pan) {
            int sum = 0;
            for (int i = frompos; i < topos; i++) {
                seat.everydayticket[i] -= buynum;
            }
            if (frompos == 0) {
                sum = tmptrain.sumprices[topos - 1];
            } else {
                sum = tmptrain.sumprices[topos - 1] - tmptrain.sumprices[frompos - 1];
            }
            ticketbase.ticket_database.erase(fingseat);
            ticketbase.ticket_base_.erase({trainid, days_to}, fingseat);
            ticketbase.ticket_base_.insert({trainid, days_to}, ticketbase.ticket_database.insert(seat));
            int shijianch = 0;
            for (int i = 1; i < strlen(shijianchuo.c_str()) - 1; i++) {
                shijianch = shijianch * 10 + shijianchuo[i] - '0';
            }
            orderfinish ordering(shijianch,
                                 username, buynum, trainid,
                                 from, to, frompos, topos, hisleavetime,
                                 hisarrivetime, sum, days_to, 1);
            ordering.state = 1;
            bpt_history_order.insert(username, ordering);
            cout << buynum * sum << '\n';
            return;
        } else {
            if (ifq == 0) {
                cout << "-1\n";
            } else {
                cout << "queue\n";
                int sum = 0;
                if (frompos == 0) {
                    sum = tmptrain.sumprices[topos - 1];
                } else {
                    sum = tmptrain.sumprices[topos - 1] - tmptrain.sumprices[frompos - 1];
                }
                int shijianch = 0;
                for (int i = 1; i < strlen(shijianchuo.c_str()) - 1; i++) {
                    shijianch = shijianch * 10 + shijianchuo[i] - '0';
                }
                orderfinish ordering(shijianch,
                                     username, buynum, trainid,
                                     from, to, frompos, topos, hisleavetime,
                                     hisarrivetime, sum, days_to, 2);
                ordering.state = 2;
                bpt_history_order.insert(username, ordering);
                bpt_order.insert({trainid, days_to}, ordering);
            }
            return;
        }

//        sjtu::vector<orderfinish> ticketvec = bpt_order.find({trainid, hisleavetime});
//        auto begin = ticketvec.begin();
//        for (int i = 0; i < ticketvec.size(); i++) {
//            if ((*begin).buynum <=)
//        }
//        sjtu::vector<station> tmpstation(tmptrain.stations);
//        sjtu::vector<int> tmpstop(tmptrain.stopoverTimes);
//        sjtu::vector<int> tmptraveltime(tmptrain.traveltime);
//        auto begin = tmptrain.stations.begin();
//        auto iterstation = begin;
//        auto iterstop = tmptrain.stopoverTimes.begin();
//        auto itertravel = tmptrain.traveltime.begin();
//        auto end = tmptrain.stations.end();
//
//        Time statingtime(tmptrain.saledatamonth1, tmptrain.starttime);
//        Time now(statingtime);
//        auto iterfrom = tmptrain.stations.find(iterstation, end, from);
//        auto iterto = tmptrain.stations.find(iterstation, end, to);
//        if (iterfrom == end || iterto == end || (iterfrom - iterto >= 0)) {
//            cout << "-1\n";
//            return;
//        }
//        while (iterstation != iterfrom) {
//            statingtime = statingtime + (*iterstop) + (*itertravel);
//            iterstation++;
//            iterstop++;
//            itertravel++;
//        }
//        int days_to = statingtime.days_to(now);
//        if (statingtime.days_to(date) > 0) {
//            cout << "-1\n";
//            return;
//        }
//        auto changeseat = bpt_seaat.find(trainid)[0];
//        int nowseat = changeseat.everydayseat[days_to].nowseat[iterfrom - tmptrain.stations.begin()];
//        saijinqu();//将票更新
//        if (nowseat >= buynum) {
//            bpt_seaat.erase(trainid, changeseat);
//            int sum = 0;
//            int p1 = iterfrom - begin;
//            for (int i = 0; i < iterto - iterfrom; i++) {
//                changeseat.everydayseat[days_to].nowseat[p1 + i] = nowseat - buynum;
//                sum += tmptrain.prices[p1 + i];
//            }
//            bpt_seaat.insert(trainid, changeseat);
//            cout << sum * buynum << '\n';
//            return;
//        } else {
//            if (ifq) {
//                bpt_seaat.erase(trainid, changeseat);
//                int p1 = iterfrom - begin;
//                for (int i = 0; i < iterto - iterfrom; i++) {
//                    changeseat.everydayseat[days_to].waiting_line[p1 + i] = buynum;
//                }
//            } else {
//                cout << "-1\n";
//            }
//            return;
//        }
    } else if (tmp == "query_order") {
        tmp = mytoken.nextToken();
        tmp = mytoken.nextToken();
        char user[21];
        strcpy(user, tmp.c_str());
        class username tmppp(user);
        if (usership.loginmembers.find(tmppp.hashing)==usership.loginmembers.end()) {
            cout << "-1\n";
            return;
        }
        sjtu::vector<orderfinish> vec(bpt_history_order.find(user));
        cout << vec.size() << '\n';
        for (auto iter = vec.begin(); iter != vec.end(); iter++) {
            if ((*iter).state == 1) {
                cout << "[success] " << (*iter).trainid << ' ' << (*iter).from.name << ' '
                     << (*iter).leavingtime.toString() << " -> " << (*iter).to.name << ' '
                     << (*iter).arrivingtime.toString() << ' ' << (*iter).price <<
                     ' ' << (*iter).buynum << '\n';
            } else if ((*iter).state == 2) {
                cout << "[pending] " << (*iter).trainid << ' ' << (*iter).from.name << ' '
                     << (*iter).leavingtime.toString() << " -> " << (*iter).to.name << ' '
                     << (*iter).arrivingtime.toString() << ' ' << (*iter).price <<
                     ' ' << (*iter).buynum << '\n';
            } else {
                cout << "[refunded] " << (*iter).trainid << ' ' << (*iter).from.name << ' '
                     << (*iter).leavingtime.toString() << " -> " << (*iter).to.name << ' '
                     << (*iter).arrivingtime.toString() << ' ' << (*iter).price <<
                     ' ' << (*iter).buynum << '\n';
            }
        }
    } else if (tmp == "refund_ticket") {
        int n = 1;
        char user[21];
        while ((tmp = mytoken.nextToken()) != "") {
            if (tmp == "-u") {
                tmp = mytoken.nextToken();
                strcpy(user, tmp.c_str());
                class username tmppp(user);
                if (usership.loginmembers.find(tmppp.hashing)==usership.loginmembers.end()) {
                    cout << "-1\n";
                    return;
                }

            } else {
                tmp = mytoken.nextToken();
                n = mytoken.check_num(tmp);
            }
        }
        sjtu::vector<orderfinish> ordertmp = bpt_history_order.find(user);
        if (ordertmp.size() < n) {
            cout << "-1\n";
            return;
        }
        auto iter = ordertmp.begin();

        iter += (n - 1);
        if ((*iter).state == 1) {
            cout << "0\n";
            bpt_history_order.erase(user, (*iter));
            (*iter).state = 3;
            bpt_history_order.insert(user, (*iter));
            //调座位
            int finggseat = ticketbase.ticket_base_.find({(*iter).trainid, (*iter).days_to})[0];
            everydayticketsys seart = ticketbase.ticket_database.find(finggseat);
            ticketbase.ticket_base_.erase({(*iter).trainid, (*iter).days_to}, finggseat);
            ticketbase.ticket_database.erase(finggseat);
            for (int i = (*iter).frompos; i < (*iter).topos; i++) {
                seart.everydayticket[i] += (*iter).buynum;
            }
            sjtu::vector<orderfinish> changrorder = bpt_order.find({(*iter).trainid, (*iter).days_to});
            for (int i = changrorder.size() - 1; i >= 0; i--) {
                orderfinish tmpor(changrorder[i]);
                int pan = 1;
                for (int j = tmpor.frompos; j < tmpor.topos; j++) {
                    if (tmpor.buynum > seart.everydayticket[j]) {
                        pan = 0;
                        break;
                    }
                }
                if (pan == 0) {
                    continue;
                }
                for (int j = tmpor.frompos; j < tmpor.topos; j++) {
                    seart.everydayticket[j] -= tmpor.buynum;
                }
                bpt_history_order.erase(tmpor.username, tmpor);
                bpt_order.erase({(*iter).trainid, (*iter).days_to}, tmpor);
                tmpor.state = 1;
                bpt_history_order.insert(tmpor.username, tmpor);

            }
//            std::queue<orderfinish>st;
//            for(auto itere=changrorder.begin();itere!=changrorder.end();itere++){
//                st.push((*itere));
//            }
//            while(!st.empty()){
//                orderfinish tmpor(st.front());
//                st.pop();
//                int topos=tmpor.topos;
//                int pan=1;
//                for(int i=tmpor.frompos;i<topos;i++){
//                    if(tmpor.buynum>seart.ticket[i]) {
//                        pan = 0;
//                        break;
//                    }
//                }
//                if(pan==0)continue;
//                for(int i=tmpor.frompos;i<topos;i++){
//                    seart.ticket[i]-=tmpor.buynum;
//                }
//                //调整订单
//                bpt_history_order.erase(tmpor.username,tmpor);
//                bpt_order.erase({(*iter).trainid,(*iter).days_to},tmpor);
//                tmpor.state=1;
//                bpt_history_order.insert(tmpor.username,tmpor);
//            }
            ticketbase.ticket_base_.insert({(*iter).trainid, (*iter).days_to},
                                           ticketbase.ticket_database.insert(seart));
            return;
        } else if ((*iter).state == 2) {
            cout << "0\n";
            bpt_history_order.erase(user, (*iter));
            bpt_order.erase({(*iter).trainid, (*iter).days_to}, (*iter));
            (*iter).state = 3;
            bpt_history_order.insert(user, (*iter));
            return;
        } else {
            cout << "-1\n";
            return;
        }

    } else if (tmp == "clean") {
        cout << "0\n";
        usership.clear();
        usership.loginmembers.clear();
        trainrelease.clear("release.db");
        bpt_order.clear("orderfinish.db");
        bpt_seaat.clear("seat.db");
        bpt_history_order.clear("history.db");
        station_to_trainid.clear("station_to_train.db");
        bpt_train.bpt_train.clear("bpt_train");
        return;
    } else if (tmp == "exit") {
//        usership.offline();

        ifout = 1;
        return;
    }


}
#endif //UNTITLED97_INSTRUCTIONS_H
