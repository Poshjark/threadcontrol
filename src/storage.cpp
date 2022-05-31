#include "storage.h"
#include <thread>
#include <string>

void Storage::sort(){
        while(unsorted){
            auto& l = container;
            if (!l.empty()) {
                int start = 0;
                int end = l.size() - unsorted;

                auto element = l.begin();
                std::advance(element, end);
                auto value = *element;

                auto mid_it = l.begin();
                int mid = start + (end - start) / 2;
                std::advance(mid_it, mid);

                int diff = 0;
                while (start <= end) {
                    std::advance(mid_it, diff);
                    mid += diff;
                    if (mid_it != l.end() && value == *mid_it) {
                        break;
                    }
                    else if (mid_it != l.end() && value < *mid_it ) {
                        end = mid - 1;
                    }
                    else {
                        start = mid + 1;
                    }
                    diff = start + ((end - start) / 2) - mid;
    
                }
                while(mid_it != element && mid_it != l.end() &&  value > *mid_it ){
                    mid_it++;
                }
                l.insert(mid_it, value);
                l.erase(element);
                unsorted--;
            }
        }
    }

void Storage::push(Color value) {
    container.push_back(value);
    unsorted++;
}

void Storage::push_random(){
    auto random_color = "rgb"[std::rand() % 3];
    this->push(static_cast<Color>(random_color));
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // It's here not to generate too many elements.
}

void Storage::print() {
    print_std_container(container);
}

bool Storage::test_data() {
    if (container.size()) {
        for (auto it = container.begin(), itnext = ++container.begin(); itnext != container.end(); it++, itnext++) {
            if (*it > *itnext) {
                return false;
            }
        }
    }
    return true;
}