#include <iostream>
#include <array>
#include <string>


class Sensor {
	private: 
		Sensor(){};

		std::array<std::string, 4> led = {"LED TURNED OFF","YELLOW LED ON","GREEN LED ON","RED LED ON!"};
	public: 
		Sensor(const Sensor&) = delete;
		static Sensor& getInstance(){
			static Sensor instance;
			return instance;
		}

		const std::array<std::string, 4>& getLed() const {
			return led;
		}
};


class FiniteSateMachine {
	private: 
		FiniteSateMachine() {};
		std::array<char, 4> inputs ={'a', 'a', 'b', 'c'};
		int inputSize = sizeof(inputs)/sizeof(inputs[0]);
		static int index;

	public: 
		FiniteSateMachine(const FiniteSateMachine&) = delete;
		static FiniteSateMachine& getInstance() {
			static FiniteSateMachine instance;
			return instance;
		}

		static int currentState;
		
		void setCurrentState(int state) const {
			currentState = state;
		}
		int getCurrentState() const {
			return currentState;
		}
		char next_input() const {
			if (index>=inputSize) {
				std::cout << "Input quantity overflow" << std::endl;
				return 'x'; 
			}
			return inputs[index++];
		}

		/*
		return 2 >= 0; returning correctly the next state
		return -1; character not allowed in that state
		return -2; out of bound of inputs
		return -3; internal error
		return 3; Final state reached
		*/
		int computeNextState(int currentState, char character) const {
			switch(currentState) {
				case 0:
					switch(character) {
						case 'x' :return -2;
						case 'a' : 
							setCurrentState(2);
							return 2;
						case 'b' : 
							setCurrentState(1);
							return 1;
						case 'c': 
							setCurrentState(3);
							return 3; 
						break;
					}
					break;
				case 1: 
					switch(character) {
						case 'x' :return -2;
						case 'b' : 
							setCurrentState(1);
							return 1;
						case 'c' : 
							setCurrentState(3);
							return 3; 
						case 'a' : return -1;
						break;

					}
					break;
				case 2:
					switch(character) {
						case 'x' :return -2;
						case 'a' : 
							setCurrentState(0);	
							return 0;
						case 'b' : return -1;
						case 'c': return -1; 
						break;
					}
					break;
				case 3: 
					return 3;
					break;
			}
			return -3;
		}

		void computeOutput (int currentState, int nextState, const Sensor& sensor) const {
			const std::array<std::string, 4>& led = sensor.getLed();
			std::cout << "Board switched from " << currentState << " to " << nextState << std::endl;
			switch(nextState){
				case 0:
					std::cout << led[0] << std::endl;
					break;
				case 1:
					std::cout << led[1] << std::endl;
					break;
				case 2:
					std::cout << led[2] << std::endl;
					break;
				case 3:
					std::cout << led[3] << std::endl;
					std::cout << "EVERYTHING IS BLOCKED!!!" << std::endl;
					break;
				case -1: 
					std::cout << "Next state not allowed from this state" << std::endl; 
					break;
				case -2:
					std::cout << "Input out of bound, modify the input array size if you want to give more inputs to the board" << std::endl;
					break;
				case -3:
					std::cout << "Internal error, idk" << std::endl;
					break;
				default:
					std::cout << "Unknown state" << std::endl;
					break;
				break;
			}
		
		}
};




int FiniteSateMachine::index = 0;
int FiniteSateMachine::currentState = 0;

int main()
{
	const FiniteSateMachine& Fsm = FiniteSateMachine::getInstance();
	const Sensor& SensorInstance = Sensor::getInstance();
	char character;

	while(1)
	{
		int prevState = Fsm.getCurrentState();
		character = Fsm.next_input();
		int nextState = Fsm.computeNextState(prevState,character);
		Fsm.computeOutput(prevState,nextState,SensorInstance);

		if (character == 'x' || nextState == 3) {
			break;
		}
	}
	
	return 0;

}