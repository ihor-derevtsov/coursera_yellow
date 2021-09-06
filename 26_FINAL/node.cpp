#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) const { return true; }

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date) : cmp_(cmp), date_(date) {}
bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
    if (cmp_ == Comparison::Less) { return date < date_; }
    else if (cmp_ == Comparison::LessOrEqual) { return date <= date_; }
    else if (cmp_ == Comparison::Greater) { return date_ < date; }
    else if (cmp_ == Comparison::GreaterOrEqual) { return date_ <= date; }
    else if (cmp_ == Comparison::Equal) { return date == date_; }
    else { return !(date == date_); } // else if (cmp_ == Comparison::NotEqual)
}

EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& value) : cmp_(cmp), value_(value) {}
bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
    if (cmp_ == Comparison::Less) { return event < value_; }
    else if (cmp_ == Comparison::LessOrEqual) { return event <= value_; }
    else if (cmp_ == Comparison::Greater) { return value_ < event; }
    else if (cmp_ == Comparison::GreaterOrEqual) { return value_ <= event; }
    else if (cmp_ == Comparison::Equal) { return value_ == event; }
    else { return !(value_ == event); }
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& logical_operation, 
    shared_ptr<Node> left, shared_ptr<Node> right)
    : logical_operation_(logical_operation), left_(left), right_(right) {}
    
bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
    if (logical_operation_ == LogicalOperation::Or) {
        return left_->Evaluate(date, event) ||  right_->Evaluate(date, event);
    } else { return left_->Evaluate(date, event) &&  right_->Evaluate(date, event); } // And
}