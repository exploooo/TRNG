% Nazwa pliku
filename = 'wyniki.txt';

% Wczytanie danych z pliku
data = load(filename);

% Sprawdzenie, czy dane zostały poprawnie wczytane
if isempty(data)
    error('Nie udało się wczytać danych z pliku');
end

% Generowanie histogramu
figure; % Tworzenie nowego okna z wykresem
hist(data, 'BinMethod', 'auto'); % Automatyczny dobór liczby przedziałów
title('Histogram danych z pliku');
xlabel('Wartości');
ylabel('Częstość');

% Dodatkowe ustawienia (opcjonalne)
grid on; % Włączenie siatki
