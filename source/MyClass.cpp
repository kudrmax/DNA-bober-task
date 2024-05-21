#pragma once

#include "MyClass.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <deque>
#include <vector>

MyClass::MyClass(const std::string& file_name) {
    std::ifstream infile(file_name);
    std::string line;
    int num;
    std::deque<std::string> q;
    while (std::getline(infile, line))
        q.push_back(line);

    int n = std::stoi(q.front());
    q.pop_front();

    auto parents_str = q.front();
    std::vector<int> parents;
    std::stringstream parents_sstream(parents_str);
    while (parents_sstream >> num)
        parents.push_back(num);
    q.pop_front();

    auto values_str = q.front();
    std::vector<int> values;
    std::stringstream values_sstream(values_str);
    while (values_sstream >> num)
        values.push_back(num);
    q.pop_front();

    int diseases_n = std::stoi(q.front());
    q.pop_front();

    std::vector<std::vector<int>> diseases;
    for (int i = 0; i < diseases_n; ++i) {
        auto disease_str = q.front();
        std::vector<int> disease;
        std::stringstream disease_sstream(disease_str);
        while (disease_sstream >> num)
            disease.push_back(num);
        q.pop_front();
        diseases.push_back(disease);
    }

    int patients_n = std::stoi(q.front());
    q.pop_front();

    std::vector<std::vector<int>> patients;
    for (int i = 0; i < patients_n; ++i) {
        auto patient_str = q.front();
        std::vector<int> patient;
        std::stringstream patient_sstream(patient_str);
        while (patient_sstream >> num)
            patient.push_back(num);
        q.pop_front();
        patients.push_back(patient);
    }

    m_count = n;
    m_parents = std::move(parents);
    m_values = std::move(values);
    m_diseases = std::move(diseases);
    m_patients = std::move(patients);
    fill_hmaps();
}

void MyClass::fill_hmaps() {
    m_values_hmap[1] = m_values[0];
    for (int i = 0; i < m_parents.size(); ++i) {
        auto child_index = i + 2;
        auto parent_index = m_parents[i];

        m_parents_hmap[child_index] = parent_index;
        m_children_hmap[parent_index].push_back(child_index);
        m_values_hmap[child_index] = m_values[i + 1];
    }

    for (int i = 1; i < m_count + 1; ++i) {
        auto el = i;
        auto depth = 0;
        while (el != 1) {
            el = m_parents_hmap[el];
            ++depth;
        }
        m_depth_hmap[i] = depth;
    }
}

int MyClass::find_common_parent(int i1, int i2) {
    if (i1 > i2)
        std::swap(i1, i2);
    auto i1_orig = i1;
    auto i2_orig = i2;
    auto depth1 = m_depth_hmap[i1];
    auto depth2 = m_depth_hmap[i2];
    auto vertexes = std::make_pair(i1, i2);
    if (m_common_parent.find(vertexes) != m_common_parent.end())
        return m_values_hmap[m_common_parent[vertexes]];

    if (depth1 < depth2) {
        std::swap(depth1, depth2);
        std::swap(i1, i2);
    }

    while (depth1 > depth2) {
        depth1 -= 1;
        i1 = m_parents_hmap[i1];
    }

    while (i1 != i2) {
        --depth1;
        --depth2;
        i1 = m_parents_hmap[i1];
        i2 = m_parents_hmap[i2];
    }

    m_common_parent[{i1_orig, i2_orig}] = i1;
    return m_values_hmap[i1];
}

std::vector<int> MyClass::main_foo() {
    std::vector<int> res;

    for (int i = 0; i < m_patients.size(); ++i) {
        if (i % 100 == 0)
            std::cout << i << "/" << m_patients.size() << std::endl;
        auto patient = m_patients[i];
        int IC_LCA_sum_max = 0;
        int best_k = -10;
        for (int k = 0; k < m_diseases.size(); ++k) {
            auto disease = m_diseases[k];
            int IC_LCA_sum = 0;
            for (const auto& p: patient) {
                int IC_LCA_max = 0;
                for (const auto& d: disease) {
                    int IC_LCA = find_common_parent(p, d);
                    IC_LCA_max = std::max(IC_LCA_max, IC_LCA);
                }
                IC_LCA_sum += IC_LCA_max;
            }
            if (IC_LCA_sum > IC_LCA_sum_max) {
                IC_LCA_sum_max = IC_LCA_sum;
                best_k = k;
            }
        }
        res.push_back(best_k + 1);
    }

    return res;
}

void MyClass::print_data() {
    std::cout << m_count << std::endl;
    for (const auto& el: m_parents)
        std::cout << el << " ";
    std::cout << std::endl;
    for (const auto& el: m_values)
        std::cout << el << " ";
    std::cout << std::endl;
    for (const auto& disease: m_diseases) {
        for (const auto& d: disease)
            std::cout << d << " ";
        std::cout << std::endl;
    }
    for (const auto& patient: m_patients) {
        for (const auto& p: patient)
            std::cout << p << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}