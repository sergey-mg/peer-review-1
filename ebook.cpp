#include <iomanip>
#include <iostream>
#include <istream>
#include <ostream>
#include <ranges>
#include <vector>

namespace view = std::ranges::views;

class Ebook {
   public:
    void Solve(std::istream& is, std::ostream& os) {
        int n;
        is >> n;
        os << std::setprecision(6);
        for (int _ : view::iota(0, n)) {
            std::string command;
            is >> command;
            if (command == "READ") {
                Read(is);
            } else if (command == "CHEER") {
                CheerReader(is, os);
            }
        }
    }

   private:
    std::vector<int> user_to_pages_read;
    std::vector<int> page_to_achieved_users_;
    int total_users_ = 0;

    void CheerReader(std::istream& is, std::ostream& os) {
        int user_id;
        is >> user_id;
        if ((int)user_to_pages_read.size() < user_id) {
            user_to_pages_read.resize(user_id * 2);
        }
        int read_pages = user_to_pages_read[user_id - 1];
        if (read_pages) {
            if (total_users_ - 1) {
                os << (total_users_ - page_to_achieved_users_[read_pages - 1]) *
                          1.0 / (total_users_ - 1)
                   << "\n";
            } else {
                os << "1" << "\n";
            }
        } else {
            os << "0" << "\n";
        }
    }

    void Read(std::istream& is) {
        int user_id, read_pages;
        is >> user_id >> read_pages;
        if ((int)user_to_pages_read.size() < user_id) {
            user_to_pages_read.resize(user_id * 2);
        }
        if ((int)page_to_achieved_users_.size() < read_pages) {
            page_to_achieved_users_.resize(read_pages * 2);
        }

        if (!user_to_pages_read[user_id - 1]) {
            ++total_users_;
        }
        for (int i : view::iota(user_to_pages_read[user_id - 1], read_pages)) {
            ++page_to_achieved_users_[i];
        }
        user_to_pages_read[user_id - 1] = read_pages;
    }
};

int main() {
    Ebook ebook;
    ebook.Solve(std::cin, std::cout);
}