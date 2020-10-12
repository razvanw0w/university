package ro.stackoverflowpioneers.ConferenceManagementSystem.Controller;

import org.junit.Before;
import org.junit.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.ResultActions;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.setup.MockMvcBuilders;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.ConferenceSection;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.Room;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Repository.ConferenceSectionRepository;

import java.util.Arrays;
import java.util.Date;
import java.util.List;

import static org.hamcrest.Matchers.hasSize;
import static org.hamcrest.Matchers.is;
import static org.mockito.Mockito.when;
import static org.mockito.MockitoAnnotations.initMocks;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

public class ConferenceSectionControllerTest {
    private MockMvc mockMvc;

    @InjectMocks
    private ConferenceSectionController conferenceSectionController;

    @Mock
    private ConferenceSectionRepository conferenceSectionRepository;

    private ConferenceSection section1;
    private ConferenceSection section2;

    @Before
    public void setup() throws Exception {
        initMocks(this);
        this.mockMvc = MockMvcBuilders.standaloneSetup(conferenceSectionController).build();
        initData();
    }

    private void initData() {
        section1 = new ConferenceSection("s1", new Date(), new Date());
        section1.setId(1);
        section1.setRoom(new Room());
        section1.setRoomNumber(1);
        section2 = new ConferenceSection("s2", new Date(), new Date());
        section2.setId(2);
        section2.setRoom(new Room());
        section2.setRoomNumber(2);
    }

    @Test
    public void getAllConferenceSection() throws Exception {
        List<ConferenceSection> sections = Arrays.asList(section1, section2);
        when(conferenceSectionRepository.findAll()).thenReturn(sections);

        ResultActions resultActions = mockMvc.perform(MockMvcRequestBuilders.get("/conferencesections/all"))
                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON))
                .andExpect(jsonPath("$", hasSize(2)))
                .andExpect(jsonPath("$[0].id", is(1)))
                .andExpect(jsonPath("$[1].id", is(2)))
                .andExpect(jsonPath("$[0].name", is("s1")))
                .andExpect(jsonPath("$[1].name", is("s2")));
    }
}
