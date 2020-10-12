package ro.stackoverflowpioneers.ConferenceManagementSystem.Controller;

import org.junit.Before;
import org.junit.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.setup.MockMvcBuilders;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.Room;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Repository.RoomRepository;

import java.util.Arrays;
import java.util.List;

import static org.hamcrest.Matchers.hasSize;
import static org.hamcrest.Matchers.is;
import static org.mockito.Mockito.when;
import static org.mockito.MockitoAnnotations.initMocks;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

public class RoomControllerTest {
    private MockMvc mockMvc;

    @InjectMocks
    private RoomController roomController;

    @Mock
    private RoomRepository roomRepository;

    private Room room1;
    private Room room2;

    @Before
    public void setup() throws Exception {
        initMocks(this);
        this.mockMvc = MockMvcBuilders.standaloneSetup(roomController).build();
        initData();
    }

    @Test
    public void getAllRooms() throws Exception {
        List<Room> rooms = Arrays.asList(room1, room2);
        when(roomRepository.findAll()).thenReturn(rooms);
        mockMvc.perform(MockMvcRequestBuilders.get("/rooms/all"))
                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON))
                .andExpect(jsonPath("$", hasSize(2)))
                .andExpect(jsonPath("$[0].id", is(1)))
                .andExpect(jsonPath("$[1].id", is(2)))
                .andExpect(jsonPath("$[0].number", is(1)))
                .andExpect(jsonPath("$[1].number", is(2)));
    }

    private void initData() {
        room1 = new Room();
        room1.setId(1);
        room1.setNumber(1);
        room2 = new Room();
        room2.setId(2);
        room2.setNumber(2);
    }

}
