#include <iomanip>
#include <iostream>
#include <istream>
#include <ostream>
#include <ranges>
#include <vector>

namespace view = std::ranges::views;

class Ebook {
   public:
    double CheerReader(size_t user_id) {
        if (user_to_pages_read.size() < user_id) {
            user_to_pages_read.resize(user_id * 2);
        }
        int read_pages = user_to_pages_read[user_id - 1];
        if (read_pages) {
            if (total_users_ - 1) {
                return (total_users_ -
                        page_to_achieved_users_[read_pages - 1]) *
                       1.0 / (total_users_ - 1);
            } else {
                return 1.0;
            }
        } else {
            return 0.0;
        }
    }

    void Read(size_t user_id, size_t read_pages) {
        if (user_to_pages_read.size() < user_id) {
            user_to_pages_read.resize(user_id * 2);
        }
        if (page_to_achieved_users_.size() < read_pages) {
            page_to_achieved_users_.resize(read_pages * 2);
        }

        if (!user_to_pages_read[user_id - 1]) {
            ++total_users_;
        }
        for (size_t i :
             view::iota(user_to_pages_read[user_id - 1], read_pages)) {
            ++page_to_achieved_users_[i];
        }
        user_to_pages_read[user_id - 1] = read_pages;
    }

   private:
    std::vector<size_t> user_to_pages_read;
    std::vector<size_t> page_to_achieved_users_;
    size_t total_users_ = 0;
};

void ParseRequests(std::istream& is, std::ostream& os, Ebook& ebook) {
    int n;
    is >> n;
    os << std::setprecision(6);
    for (int _ : view::iota(0, n)) {
        std::string command;
        is >> command;
        if (command == "READ") {
            size_t user_id, page;
            is >> user_id >> page;
            ebook.Read(user_id, page);
        } else if (command == "CHEER") {
            size_t user_id;
            is >> user_id;
            os << ebook.CheerReader(user_id) << "\n";
        }
    }
}

int main() {
    Ebook ebook;
    ParseRequests(std::cin, std::cout, ebook);
}