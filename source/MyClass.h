#include <string>
#include <vector>
#include <unordered_map>
#include <boost/functional/hash.hpp>


class MyClass {
public:
    MyClass(const std::string& file_name);
    void print_data();
    std::vector<int> main_foo();
private:
    void fill_hmaps();
    int find_common_parent(int i1, int i2);
private:
    int m_count;
    std::vector<int> m_parents;
    std::vector<int> m_values;
    std::vector<std::vector<int>> m_diseases;
    std::vector<std::vector<int>> m_patients;
private:
    std::unordered_map<int, int> m_parents_hmap;
    std::unordered_map<int, std::vector<int>> m_children_hmap;
    std::unordered_map<int, int> m_values_hmap;
    std::unordered_map<int, int> m_depth_hmap;
//    std::unordered_map<int, std::unordered_map<int, int>> m_common_parent;
    std::unordered_map<std::pair<int, int>, int, boost::hash<std::pair<int, int>>> m_common_parent;
};
