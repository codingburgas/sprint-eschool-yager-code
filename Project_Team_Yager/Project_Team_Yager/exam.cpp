char get_rating(double percentage) {
    if (percentage >= 90.0) return 'A';
    else if (percentage >= 80.0) return 'B';
    else if (percentage >= 70.0) return 'C';
    else if (percentage >= 60.0) return 'D';
    else return 'F';
}