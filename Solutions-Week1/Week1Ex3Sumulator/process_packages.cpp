#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
        size_(size),
        finish_time_()
    {}

    Response Process(const Request &request) {
        // write your code here

		// Clear all passed requests
		while (!finish_time_.empty()) {
			int cur_finish = finish_time_.front();
			if (cur_finish <= request.arrival_time) {
				finish_time_.pop_front();
			}
			else {
				break;
			}
		} 

		// If empty, proccess right now
		if (finish_time_.empty()) {
			finish_time_.push_back(request.arrival_time + request.process_time);

			return Response(false, request.arrival_time);
		}

		// If Full, drop
		if (finish_time_.size() == size_) {
			return Response(true, -1);
		}

		// Otherwise - we must put in queue if we can
		int last_finish = finish_time_.back();
		finish_time_.push_back(last_finish + request.process_time);
		return Response(false, std::max(last_finish, request.arrival_time));
    }
private:
    int size_;
    std::deque <int> finish_time_;
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
