// Laba_01.cpp 
//

#include <iostream>
#include <vector>

using namespace std;

vector<double> input_numbers(size_t count) {
    vector<double> result(count);
    cout << "Enter Numbers  " ;
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

void find_minmax(const vector<double>& numbers, double& min, double& max) {
    min = numbers[0];
    max = numbers[0];
    for (double number : numbers) {
        if (min > number) {
            min = number;
        }
        if (max < number) {
            max = number;
        }
    }
}

vector<size_t> make_histogram(vector<double> numbers, size_t bin_count, size_t number_count) {
    double min = numbers[0];
    double max = numbers[0];
    for (double number : numbers) {
        if (min > number) {
            min = number;
        }
        if (max < number) {
            max = number;
        }
    }
    vector<size_t> bins(bin_count, 0);
    double bin_size = (max - min) / bin_count;
    for (size_t i = 0; i < number_count; i++) {
        bool found = false;
        for (size_t j = 0; j < (bin_count - 1.0) && (!found) ; j++) {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1.0) * bin_size;
            if (lo <= numbers[i] && (numbers[i] < hi)) {
                bins[j]++;
                found = true;
            }
        }
        if (!found) {
            bins[bin_count - 1]++;
        };
    } 
    return bins;
}

void show_histogram_text(vector<size_t> bins, size_t scale_count) {
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTRERISK = SCREEN_WIDTH - 3 - 1;
    size_t max_bin = bins[0];//максимальная высота столбца
    for (size_t bin : bins) {
        if (max_bin < bin) {
            max_bin = bin;
        }
    }

    size_t max_height = 0;
    bool flag = false;

    for (size_t bin : bins) {
        size_t height = bin;

        if (max_bin > MAX_ASTRERISK) {
            height = MAX_ASTRERISK * (static_cast<double>(bin) / max_bin);
            flag = true;
        }
        if (height > max_height) {
            max_height = height;
        }

        if (height < 100) {
            cout << " ";
        }
        if (height < 10) {
            cout << " ";
        }
        cout << height << "|";
        for (size_t i = 0; i < height; i++) {
            cout << "*";
        }
        cout << endl;
    }
    // создание шкалы
    //cout << endl;
    cout << "   |";
    if (flag) {
        max_bin = max_height;
    }

    for (size_t i = 0; i < max_bin; i += scale_count) {
        for (int j = 0; j < (scale_count - 1.0); j++) {
            cout << "-";
        };
        cout << "|";
    };
    cout << endl;
    cout << "   0";
    for (size_t i = 0; i < (scale_count - 1.0); i++) {
        cout << " ";
    }

    cout << scale_count;
    if (max_bin > scale_count) {
        size_t counter;

        for (counter = 2.0 * scale_count; counter < max_bin; counter += scale_count) {
            for (size_t j = 0; j < scale_count; j++) {
                cout << " ";
            };
        }
        for (size_t i = 0; i < (scale_count - 1.0); i++) {
            cout << " ";
        }
        cout << counter << endl;
    }
}



int main()
{
    // ввод данных
    size_t number_count;
    cout << "Enter number count: ";
    cin >> number_count;

    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cout << "Enter  bin_count: ";
    cin >> bin_count;

    size_t scale_count;
    cout << "Enter Scale : ";
    cin >> scale_count;

    // проверка корректности введенного шага 
    if ((scale_count < 4) || (scale_count > 9)) {
        cout << endl;
        cout  << "Error ";
        return 0;
    }
    // расчет гистограммы

    const auto bins = make_histogram(numbers, bin_count,number_count);

    // вывод гистограммы 

    show_histogram_text(bins, scale_count);

}


