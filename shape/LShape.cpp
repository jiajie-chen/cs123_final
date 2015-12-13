#include "LShape.h"
#include "Shape.h"
#include "vector"



#define UP_THETA (float) M_PI/12
#define LEFT_THETA (float)M_PI/15.0f
#define H_THETA (float) M_PI/12.0f
#define D_LENGTH (float).01f
#define D_WIDTH (float).01f

LShape::LShape(state start_state, std::string rules, GLuint vertexAttribIndex, GLuint normalAttribIndex, GLuint texCoordAttribIndex)
    : Shape(vertexAttribIndex, normalAttribIndex, texCoordAttribIndex) {
    m_state_stack = std::vector<state>();
    m_current_state = start_state;

    for(char& command : rules) {
        switch(command){
        case 'F':
            //add to shape and move forward
            addStateToShape();
            m_current_state.position += m_current_state.heading*m_current_state.length;
        break;
        case 'f':
            //move forward
            m_current_state.position += m_current_state.heading*m_current_state.length;
        break;
        case '+':
            //turn left by UP_THETA
            m_current_state.heading = glm::rotate(m_current_state.heading, UP_THETA, m_current_state.up);
            m_current_state.left = glm::rotate(m_current_state.left, UP_THETA, m_current_state.up);
        break;
        case '-':
            //turn right by -UP_THETA
            m_current_state.heading = glm::rotate(m_current_state.heading, -UP_THETA, m_current_state.up);
            m_current_state.left = glm::rotate(m_current_state.left, -UP_THETA, m_current_state.up);
        break;
        case '&':
            // pitch down by LEFT_THETA
            m_current_state.heading = glm::rotate(m_current_state.heading, LEFT_THETA, m_current_state.left);
            m_current_state.up = glm::rotate(m_current_state.up, LEFT_THETA, m_current_state.left);
        break;
        case '^':
            // pitch up by LEFT_THETA
            m_current_state.heading = glm::rotate(m_current_state.heading, -LEFT_THETA, m_current_state.left);
            m_current_state.up = glm::rotate(m_current_state.up, -LEFT_THETA, m_current_state.left);
        break;
        case '\\':
            // roll left by H_THETA
            m_current_state.left = glm::rotate(m_current_state.left, H_THETA, m_current_state.heading);
            m_current_state.up = glm::rotate(m_current_state.up, H_THETA, m_current_state.heading);
        break;
        case '/':
            // roll right by -H_THETA
            m_current_state.left = glm::rotate(m_current_state.left, -H_THETA, m_current_state.heading);
            m_current_state.up = glm::rotate(m_current_state.up, -H_THETA, m_current_state.heading);
        break;
        case '|':
            // rotate 180ºaround up.

            //lmao can't definte M_PI/float because it makes it a double
            m_current_state.heading = glm::rotate(m_current_state.heading, (float)M_PI, m_current_state.up);
            m_current_state.left = glm::rotate(m_current_state.left, (float) M_PI, m_current_state.up);
        break;
        case '"':
            // increase length by D_LENGTH
            m_current_state.length += D_LENGTH;
        break;
        case '!':
             // increase width by D_WIDTH
            m_current_state.width += D_WIDTH;
        break;
        case '`':
            // decrease length by D_LENGTH
            m_current_state.length -= D_LENGTH;
        break;
        case '~':
            // decrease width by D_WIDTH
            m_current_state.width -= D_WIDTH;
        break;
        case '<':
            // increment the materialIdx (material selection is handled by the lsystem generator)
            m_current_state.materialIdx++;
        break;
        case '>':
            // decrement the materialIdx
            m_current_state.materialIdx--;
        break;
        case '[':
            // push the current state onto the stack
            m_state_stack.push_back(&m_current_state);
        break;
        case ']':
            // pop the state stack and set to the current state
            this->m_current_state = m_state_stack.pop_back();
        break;
        }
    }
}

LShape::~LShape() {
    delete m_state_stack

}

void LShape::addStateToShape(){
    // create verticies or polygons to the geometery represented by this LShape


}

