//
// Created by thijs on 17-10-19.
//

#ifndef SELFDRIVINGCAR_ROWCOL_H
#define SELFDRIVINGCAR_ROWCOL_H

class RowCol {
public:
    int row;
    int col;

    RowCol(int row, int col) : row(row), col(col) {}
    RowCol() : row(-1), col(-1) {}

    bool operator ==(const RowCol &other) const {
        return (this->row == other.row) && (this->col == other.col);
    }

    double dist2(const RowCol &other) const {
        return (this->row-other.row)*(this->row-other.row) + (this->col-other.col)*(this->col-other.col);
    }
};

#endif //SELFDRIVINGCAR_ROWCOL_H
