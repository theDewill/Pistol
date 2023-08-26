#include <iostream>
#include <string>
#include "headerBundle/control.h"
#include <boost/asio.hpp>
#include <thread>
#include <queue>
#include <Metal/Metal.h>
#include <ncurses.h>

//gpu acceleration code
//id<MTLDevice> device = MTLCreateSystemDefaultDevice();
//MetalAdder *adder = [[MetalAdder Alloc] initWithDevice:device];

using namespace boost::asio;
using ip::tcp;
using std::cout;
using std::endl;
using std::string;


string read_(tcp::socket & socket){
    boost::asio::streambuf buf;
    boost::asio::read_until(socket,buf, "\n");
    string data = boost::asio::buffer_cast<const char*>(buf.data());
    
    
    return data;
}


int main(int argc, const char * argv[]) {
    
    
    std::queue <string> msgbox;
    
    
    //add sending functioning
    std::thread reciever ([&msgbox](){
        //Initialize
        boost::asio::io_service io_service;
        tcp::acceptor acceptor_ (io_service, tcp::endpoint(tcp::v4() , 1234));
        tcp::socket Socket_ (io_service);
        acceptor_.accept(Socket_); //initializing listning
        
        
        //read operation
        while(true){
            string msg = read_(Socket_);
            msgbox.push(msg);
        }
    });
    
    //add addons
    std::thread printer ([&msgbox](){
        while(true){
            string msgb = msgbox.front();
            cout << msgb << endl;
            msgbox.pop();
        }
    });
    
    
    std::thread client ([](){
        cout << "this is client" << endl;
        io_service io_service;
        tcp::socket socket_ (io_service);
        socket_.connect(tcp::endpoint(ip::address::from_string("127.0.0.1"), 1234));
        
    });
    
    
    std::thread test ([](){
        int x = 10;
        int total = x +  5;
        cout << total ;
    }) ;
    
    
    
    reciever.join();
    client.join();
    test.join();
   
    
    
    
    return 0;
    
}
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
//    boost::asio::io_context io_context; //io_context obejct
//    tcp::acceptor listner(io_context, tcp::endpoint(tcp::v4(),8080)); //listner object
//    tcp::socket socket(io_context); //socket object is initialized
//    listner.accept(socket);
//    boost::asio::streambuf buffer;//buffer object
//    queue<string> queue;
//    int socket_close=0;
//    char ch; // key press
//    //so here is the stop i kept
//
//
//    //--thread for handling the recieving msgs
//    thread t1 ([&socket,&buffer,&queue,&socket_close](){
//        while(true){
//            if(socket_close==1){
//                socket.close();
//                break;
//            }
//            boost::asio::read_until(socket,buffer, "\r\n");
//            //converting the data to string
//            string data(boost::asio::buffers_begin(buffer.data()),boost::asio::buffers_end(buffer.data()));
//            queue.push(data);
//            //sending a response
//            string resp = "connection succesfull";
//            boost::asio::write(socket,boost::asio::buffer(resp));
//        }
//    });
//
//
//    //thread for handling sends
//    thread t2 ([&socket,&socket_close](){
//        string msg;
//        while(true){
//            cout<<"enter the message: ";
//            cin>>msg;
//            if(msg=="clssoc") {
//                socket_close=1;
//                break;
//            };
//            boost::asio::write(socket,boost::asio::buffer(msg));
//        }
//    });
//
//    //handling the keyboard listners
//    thread t3 ([&ch](){
//        // Initialize ncurses
//            initscr();
//            cbreak();  // Disable line buffering
//            noecho();  // Disable echoing of typed characters
//
//            // Enable keypad to capture function keys
//            keypad(stdscr, TRUE);
//
//            // Set non-blocking mode for getch()
//            nodelay(stdscr, TRUE);
//
//            // Loop to listen for keyboard events
//            int ch;
//            while (true) {
//                ch = getch();
//                if (ch == 'q' || ch == 'Q')
//                    break;
//
//                // Process the key event
//                // Example: Print the ASCII code of the pressed key
//                printw("Key pressed: %d\n", ch);
//                refresh();
//            }
//
//            // Clean up ncurses
//            endwin();
//    });
//
//
//    t1.join();
//    t2.join();
//    t3.join();
//
//    while(!queue.empty()){
//        cout << queue.front() << endl;
//        queue.pop();
//    }
    
    

