//
// Created by ash on 14.03.24.
//

#include "expression.h"

std::vector<exprToken> shunting_yard(const std::vector<exprToken> &expr) {
    std::stack<exprToken> st;
    std::vector<exprToken> ans;
    for (const auto &tk: expr) {

        if (tk.is_id()) {
            ans.push_back(tk);
        } else if (tk.is_op()) {
            while (!st.empty()) {
                auto sc = st.top();
                if (sc.is_op() &&
                    ((tk.left() && (tk.get_priority() <= sc.get_priority())) ||
                     (!tk.left() && (tk.get_priority() < sc.get_priority())))) {
                    ans.push_back(sc);
                    st.pop();
                } else {
                    break;
                }
            }
            st.push(tk);
        } else if (tk.is_open()) {
            st.push(tk);
        } else if (tk.is_close()) {
            bool pe = false;
            while (!st.empty()) {
                auto sc = st.top();
                if (sc.is_open()) {
                    pe = true;
                    break;
                } else {
                    ans.push_back(sc);
                    st.pop();
                }
            }
            if (!pe) {
                printf("Error: parentheses mismatched2\n");
                return {};
            }
            st.pop();

        } else {
            printf("Unknown token %d %d\n", tk.id, tk.type);
            return {};
        }


    }
    while (!st.empty()) {
        auto sc = st.top();
        if (sc.is_open() || sc.is_close()) {
            printf("Error: parentheses mismatched1\n");
            return {};
        }
        ans.push_back(st.top());
        st.pop();
    }

    return ans;
}
