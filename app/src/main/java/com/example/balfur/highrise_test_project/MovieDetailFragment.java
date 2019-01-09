package com.example.balfur.highrise_test_project;

import android.app.Activity;
import android.support.design.widget.CollapsingToolbarLayout;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.example.balfur.highrise_test_project.POJOs.Actor;
import com.example.balfur.highrise_test_project.POJOs.MovieDetail;

/**
 * A fragment representing a single Movie detail screen.
 * This fragment is either contained in a {@link MovieListActivity}
 * in two-pane mode (on tablets) or a {@link MovieDetailActivity}
 * on handsets.
 */
public class MovieDetailFragment extends Fragment {

    // Loads native cpp libs upon start up
    static {
        System.loadLibrary("MovieControllerJni");
    }

    // The movie this fragment is showing
    private MovieDetail mItem;

    /**
     * Mandatory empty constructor for the fragment manager to instantiate the
     * fragment (e.g. upon screen orientation changes).
     */
    public MovieDetailFragment() {
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Log.e("frag", "Got movieName " + getArguments().getString("movieName"));
        mItem = getMovieDetail(getArguments().getString("movieName"));

        Activity activity = this.getActivity();
        CollapsingToolbarLayout appBarLayout = activity.findViewById(R.id.toolbar_layout);
        if (appBarLayout != null) {
            appBarLayout.setTitle(mItem.getName());
        }

    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.movie_detail, container, false);

        // Show the dummy content as text in a TextView.
        if (mItem != null) {
            ((TextView) rootView.findViewById(R.id.movie_description)).setText(mItem.getDescription());

            RecyclerView recyclerView = rootView.findViewById(R.id.actor_recycler_view);
            recyclerView.setLayoutManager(new LinearLayoutManager(getActivity()));
            recyclerView.setNestedScrollingEnabled(false);

            ActorRecyclerAdapter actorRecyclerAdapter = new ActorRecyclerAdapter(mItem.getActors());
            recyclerView.setAdapter(actorRecyclerAdapter);

        }

        return rootView;
    }

    public native MovieDetail getMovieDetail(String name);
}
