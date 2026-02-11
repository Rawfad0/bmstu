import abc


class User:
    def __init__(self, user_id, name, balance):
        self.user_id = user_id
        self.name = name
        self.balance = balance
        self.rental_history = []
        self.active_rent = None

    def top_up_balance(self, amount):
        self.balance += amount

    def get_rental_history(self):
        return self.rental_history

    def rent_possible(self, car, distance_km):
        if self.balance >= 0 and self.active_rent is None and car.status == 'available':
            if car.__class__ == StandardCar and car.fuel_consumption * distance_km / 100 <= car.current_fuel:
                return True
            elif car.__class__ == ElectricCar and car.energy_consumption * distance_km / 100 <= car.current_charge:
                return True
        return False

    def rent_car(self, car, duration_minutes, distance_km):
        p = self.rent_possible(car, distance_km)
        if p:
            self.balance -= duration_minutes * car.price_per_minute
            self.active_rent = {
                'car': car,
                'duration': duration_minutes,
                'distance': distance_km
            }
            car.status = 'rented'
        return p

    def end_rental(self):
        if self.active_rent is not None:
            car = self.active_rent['car']
            if car.__class__ is StandardCar:
                car.current_fuel -= car.fuel_consumption * self.active_rent['distance'] / 100
            elif car.__class__ is ElectricCar:
                car.current_charge -= car.energy_consumption * self.active_rent['distance'] / 100
            self.rental_history.append(self.active_rent)
            car.status = 'available'
            self.active_rent = None


class Car(abc.ABC):
    def __init__(self, model, registration_number, price_per_minute):
        self.model = model
        self.registration_number = registration_number
        self.price_per_minute = price_per_minute
        self.status = 'available'

    @abc.abstractmethod
    def refill(self):
        pass


class StandardCar(Car):
    def __init__(self, model, registration_number, price_per_minute,
                 fuel_capacity, fuel_consumption, current_fuel):
        super().__init__(model, registration_number, price_per_minute)
        self.fuel_capacity = fuel_capacity
        self.fuel_consumption = fuel_consumption
        self.current_fuel = current_fuel

    def refill(self):
        self.current_fuel = self.fuel_capacity


class ElectricCar(Car):
    def __init__(self, model, registration_number, price_per_minute,
                 battery_capacity, energy_consumption, current_charge):
        super().__init__(model, registration_number, price_per_minute)
        self.battery_capacity = battery_capacity
        self.energy_consumption = energy_consumption
        self.current_charge = current_charge

    def refill(self):
        self.current_charge = self.battery_capacity


# Создание пользователя
user = User(user_id=1, name="Борис", balance=1000)

# Создание автомобилей
std_car = StandardCar(model="Toyota Camry", registration_number="A123BB",
                  price_per_minute=10, fuel_capacity=60, fuel_consumption=8, current_fuel=60)

# Баланс пользователя и кол-во топлива в автомобиле до аренды
print(user.balance)         # 1000
print(std_car.current_fuel)     # 60

# Попытка аренды автомобиля
user.rent_car(std_car, duration_minutes=30, distance_km=20)

# Завершение аренды
user.end_rental()

# Изменения после завершения аренды
print(user.balance)         # 700
print(std_car.current_fuel)     # 58.4

# Пополнение баланса пользователя и заправка автомобиля
user.top_up_balance(500)
std_car.refill()

# Изменения после пополнения топлива и баланса пользователя
print(user.balance)         # 1200
print(std_car.current_fuel)     # 60
